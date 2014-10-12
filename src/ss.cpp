#include <ss.h>

#define MAXPENDING 10
#define PACKET_SIZE 302
#define CHUNK_SIZE 10000
#define NUM_THREADS 10

SS::SS() {
	cd = new ChainData();
}

SS::~SS() {
	delete cd;
}
/*
*	parseUrl: Takes the given url and finds the filename from it based on the last '/' character.
*/
string SS::parseUrl(string url) {
	size_t pos = url.find_last_of("/\\");

	if ( !((pos >= 0) && (pos <= (url.length()))) ) {
		return "index.html";
	}
	return url.substr(pos+1, url.length());
}

/*
*	clientRequestConnection: handles the connection details to a server
*	Returns the socket descriptor.
*/
int SS::clientRequestConnection(string ip, string port, ChainData cdOrig) {
	struct addrinfo hints, *res;
	int clientSock;

	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = 6;

	getaddrinfo(ip.c_str(), port.c_str(), &hints, &res);

	clientSock = socket(res->ai_family, res->ai_socktype, res->ai_protocol);

	if (connect(clientSock, res->ai_addr, res->ai_addrlen) < 0) {
		cerr << "\nError connecting. Please try again." << endl;
		exit(1);
	}

	// Construct ChainData
	for (int i = 0; i < cdOrig.getSSnum(); i++) {
		cd->addEntry(cdOrig.getEntry(i).getIP(), cdOrig.getEntry(i).getPort());
	}
	cd->setSSnum(cdOrig.getSSnum());
	outgoingServerSock = clientSock;
	return clientSock;
}

/*
*	serverListen: handles the connection details from a client request
*	Returns the socket descriptor after the connection has been made.
*/
int SS::serverListen(int port) {
	listenPort = port;
	socklen_t ClientLen;
	struct sockaddr_in ServAddr, ClientAddr;
	ServAddr.sin_family = AF_INET;
	ServAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	ServAddr.sin_port = htons(listenPort);
	int serverPort = listenPort;
	int servSock;

	char ipAddress[128];
	memset(ipAddress, 0, sizeof(ipAddress));
	gethostname(ipAddress, sizeof(ipAddress));
	struct hostent *h;
	if((h=gethostbyname(ipAddress) ) == NULL ){
    	cerr << "Error getting IP address. Please try again." << endl;
    	exit(1);
    }

	if ((servSock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0) {
		cerr << "Error creating socket." << endl;
		exit(1);
	}
	while (bind(servSock, (struct sockaddr *) &ServAddr, sizeof(ServAddr)) < 0) {
		serverPort++;
		ServAddr.sin_port = htons(serverPort);
	}
	cout << "ss " <<  inet_ntoa(*((struct in_addr *)h->h_addr)) << ", " << serverPort << ":" << endl;
	listen(servSock, MAXPENDING);
	ClientLen = sizeof(ClientAddr);
	int newSock;
	if ((newSock = accept(servSock, (struct sockaddr *) &ClientAddr, &ClientLen)) < 0) {
		cerr << "Error accepting connection." << endl;
		exit(1);
	}

	incomingClientSock = newSock;
	return newSock;
}

/*
*	receiveChainData: receives each packet of the chain file and constructs a ChainData object.
*/

void SS::receiveChainData(int servSock) {
	char incomingChainBuffer[26];
	chainPacket cp;

	// Receive chaindata first
	while (1) {
		memset(incomingChainBuffer, 0, sizeof(incomingChainBuffer));
		int numBytes = recv(servSock, incomingChainBuffer, sizeof(incomingChainBuffer), 0);
		if (numBytes <= 0) {
			break;
		}
		memcpy(&cp.lastPacket, incomingChainBuffer, sizeof(cp.lastPacket)); 
		memcpy(&cp.ssNum, incomingChainBuffer+2, sizeof(cp.ssNum)); 
		memcpy(&cp.port, incomingChainBuffer+4, sizeof(cp.port));
		memcpy(&cp.ip, incomingChainBuffer+10, sizeof(cp.ip));
		cp.ssNum = ntohs(cp.ssNum);
		cp.lastPacket = ntohs(cp.lastPacket);

		if (cp.lastPacket == 2) {
			break;
		}
		cd->addEntry((string) cp.ip, (string) cp.port);
		if (cp.lastPacket == 1) {
			break;
		}
	}
}

/*
*	client: handles client operations: connection, sending requests, and relaying/writing the file.
*/
void SS::client(string ip, string port, string url, ChainData cdOrig, bool isAwget) {
	int clientSock = clientRequestConnection(ip, port, cdOrig);
	char incomingBuffer[CHUNK_SIZE];

	// Send chaindata first
	if (cd->getSSnum() != 0) {
		sendChainData(clientSock);
	}
	else {
		sendEmptyChainData(clientSock);
	}

	// Send request to server with url
	packet requestPacket;
	sendRequestPacket(requestPacket, clientSock, url);

	// Now we are waiting for the file to come back.
	cout << "\twaiting for file....." << endl;

	ofstream result;

	if (isAwget) {
		// Store the file on disk since we are at AWGET now.
		string filename = parseUrl(url);
		result.open(filename.c_str(), ofstream::binary);
		while (1) {
			memset(incomingBuffer, 0, sizeof(incomingBuffer));
			int numBytes = recv(clientSock, incomingBuffer, sizeof(incomingBuffer), 0);

			if (numBytes <= 0) {
				break;
			}
			for (int i = 0; i < numBytes; i++) {
				result << incomingBuffer[i];
			}
		}
		cout << "\tReceived file " << filename << endl;
		cout << "\tGoodbye!" << endl;
		result.close();
		close(outgoingServerSock);
	}
	else {
		// Send back to client

		cout << "\tRelaying file... " << endl;
		cout << "\tGoodbye!" << endl;
		while (1) {
			memset(incomingBuffer, 0, sizeof(incomingBuffer));
			int numBytes = recv(clientSock, incomingBuffer, sizeof(incomingBuffer), 0);

			if (numBytes <= 0) {
				break;
			}
			send(incomingClientSock, incomingBuffer, numBytes, 0);
		}
	}
	close(clientSock);
}

/*
*	server: handles the server details, listening for connection, fulfilling requests, and listening again.
*/
void SS::server(int port) {
	if (port == 0) {
		port = 29048;
	}
	int servSock;

	while (1) {
		servSock = serverListen(port);
		//int stdoutCopy = dup(serv);
		handleRequest(servSock);
	 	while (1) {
	 	 	if (!waitingOnFile) {
	 	 		break;
	 	 	}
	 	}
	}
	close(servSock);
}

/*
*	sendChainData: sends a packet for every entry in the chain file.
*/
void SS::sendChainData(int socket) {
	// Send a packet with each chainfile entry
	chainPacket cp;
	for (int i = 0; i < cd->getSSnum(); i++) {
		memset(&cp, 0, sizeof(cp));

		char chainBuffer[26];

		IpPortPair entryI = cd->getEntry(i);

		cp.ssNum = (short) cd->getSSnum();
		cp.ssNum = htons(cp.ssNum);

		char charPort[6];
		memset(charPort, 0, sizeof(charPort));
		strncpy(charPort, entryI.getPort().c_str(), sizeof(charPort));
		strncpy(cp.port, charPort, sizeof(charPort));
		cp.port[strlen(cp.port)] = '\0';

		char charIP[16];
		memset(charIP, 0, sizeof(charIP));
		strncpy(charIP, entryI.getIP().c_str(), sizeof(charIP));
		strncpy(cp.ip, charIP, sizeof(cp.ip));
		cp.ip[strlen(cp.ip)] = '\0';
			
		if (i < cd->getSSnum()-1) {
			cp.lastPacket = 0;
		}
		else {
			cp.lastPacket = 1;
		}
		cp.lastPacket = htons(cp.lastPacket);

		memcpy(chainBuffer, &cp, sizeof(chainBuffer));
		send(socket, chainBuffer, sizeof(chainBuffer), 0);
	}
}

/*
* sendEmptyChainData: Sends a dummy packet so the server knows the chainlist is empty
*/
void SS::sendEmptyChainData(int socket) {
	chainPacket cp;
	memset(&cp, 0, sizeof(cp));

	char chainBuffer[26];

	cp.ssNum = (short) cd->getSSnum();
	cp.ssNum = htons(cp.ssNum);

	char charPort[6];
	memset(charPort, 0, sizeof(charPort));
	string zeroPort = "0000";
	strncpy(charPort, zeroPort.c_str(), sizeof(charPort));
	strncpy(cp.port, charPort, sizeof(charPort));
	cp.port[strlen(cp.port)] = '\0';

	char charIP[16];
	memset(charIP, 0, sizeof(charIP));
	string zeroIP = "0.0.0.0";
	strncpy(charIP, zeroIP.c_str(), sizeof(charIP));
	strncpy(cp.ip, charIP, sizeof(cp.ip));
	cp.ip[strlen(cp.ip)] = '\0';

	cp.lastPacket = 2;
	cp.lastPacket = htons(cp.lastPacket);

	memcpy(chainBuffer, &cp, sizeof(chainBuffer));
	send(socket, chainBuffer, sizeof(chainBuffer), 0);
}

/*
* sendRequestPacket: Sends the packet with the url to the server.	
*/
void SS::sendRequestPacket(packet requestPacket, int socket, string url) {
	char requestBuffer[PACKET_SIZE];
	memset(requestBuffer, 0, sizeof(requestBuffer));
	strncpy(requestPacket.data, url.c_str(), sizeof(requestPacket.data));
	requestPacket.data[strlen(requestPacket.data)] = '\0';
	
	// Format for network
	requestPacket.dataLength = strlen(requestPacket.data);
	requestPacket.dataLength = htons(requestPacket.dataLength);

	// Copy into buffer and send
	memcpy(requestBuffer, &requestPacket, sizeof(requestBuffer));
	send(socket, requestBuffer, sizeof(requestBuffer), 0);
}

/*
*	handleRequest: handles the request from the client and either sends it on to the
*   next stepping stone or issues the 'wget' and sends it back to the client.
*/
void SS::handleRequest(int socket) {
	// First get ChainData so we have the object to update
	receiveChainData(socket);

	// Receive the packet request with the url
	packet incomingPacket;
	char incomingBuffer[PACKET_SIZE];
	memset(incomingBuffer, 0, sizeof(incomingBuffer));
	recv(socket, incomingBuffer, sizeof(incomingBuffer), 0);
	memcpy(&incomingPacket.dataLength, incomingBuffer, 2);

	// Convert back to ntohs
	incomingPacket.dataLength = ntohs(incomingPacket.dataLength);
	memset(incomingPacket.data, 0, sizeof(incomingPacket.data));
	memcpy(incomingPacket.data, incomingBuffer+2, incomingPacket.dataLength);

	string packetUrl(incomingPacket.data);
	cout << "\tRequest: " << incomingPacket.data << endl;
	cd->listEntries();

	// If this is the last stepping stone, issue the wget
	if (cd->getSSnum() == 0) {
		cout << "\tissuing wget for file " << packetUrl << endl;
		int stdoutCopy = dup(1);
		
		// redirect stdout to socket
		dup2(socket, 1);
		close(socket);

		string cmd("wget -q -O -");
		cmd += " ";
		cmd += packetUrl;

		char command[400];
		memset(incomingBuffer, 0, sizeof(incomingBuffer));
		memset(command, 0, sizeof(command));
		strncpy(command, cmd.c_str(), sizeof(command));
		command[strlen(command)] = '\0';
		system(command);

		dup2(stdoutCopy,1);
		close(stdoutCopy);
		cout << "\tFile received" << endl;
		cout << "\tGoodbye!" << endl;
		waitingOnFile = false;
	}
	else {
		// Select next stepping stone and wait for file to come back
		IpPortPair nextSSInfo = cd->getRandomEntry();
		waitingOnFile = true;
		client(nextSSInfo.getIP(), nextSSInfo.getPort(), packetUrl, *cd, false);

		close(outgoingServerSock);
		close(incomingClientSock);
		waitingOnFile = false;
	}
}