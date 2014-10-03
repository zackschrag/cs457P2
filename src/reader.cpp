#include <reader.h>

Reader::Reader(int argc, char **argv) {
	Reader::argc = argc;
	Reader::argv = argv;
	Reader::CHAINFILE = "chaingang.txt";
	cd = new ChainData();
	u = new Usage();
	validate();
}

Reader::~Reader() {
	delete cd;
	delete u;
}

bool Reader::validate() {
	// Check correct number of arguments
	if (argc != 2 && argc != 4) {
		u->printErrorAndExit("Incorrect number of arguments");
	}

	if (argc == 2) {
		bool exist = doesChainFileExist(CHAINFILE);
		if (!exist) {
			u->printErrorAndExit("chaingang.txt does not exist.");
		}
	}
	if (argc == 4) {
		return validateOptions();
	}
	return true;
}

bool Reader::validateOptions() {
	string option = (string) argv[2];
	string optionValue = (string) argv[3];

	if (option != "-c") {
		u->printErrorAndExit("");
	}

	if (optionValue.empty()) {
		u->printErrorAndExit("Please enter a filename for the '-c' option");
	}

	bool exist = doesChainFileExist(optionValue);
	if (!exist) {
		string message = optionValue + " does not exist";
		u->printErrorAndExit(message);
	}
	return true;
}

bool Reader::doesChainFileExist(string filename) {
	ifstream file(filename.c_str());
	bool good = file.good();
	file.close();
	return good;
}

void Reader::parseFile(string filename) {
	ifstream file(filename.c_str());

	string currentLine;
	string currentIP;
	int currentPort;
	getline(file, currentLine);
	/*for (unsigned int i = 0; i < currentLine.length(); i++) {
		if (!isdigit(currentLine.at(i))) {
			Usage u("Chain file is of incorrect format");
		}
	}*/
	int length = atoi(currentLine.c_str());
	int ctr = 0;

	while (ctr < length) {
		getline(file, currentLine);
		size_t pos = currentLine.find(",");
		currentIP = currentLine.substr(0,pos);
		string portString = currentLine.substr(pos+1, currentLine.length()).c_str();
		//currentPort = atoi(portString.c_str());
		ctr++;
		cd->addEntry(currentIP, portString);
	}
	cd->listEntries();
	file.close();

	IpPortPair ss = cd->getRandomEntry();
	connectToSS(ss);
}

void Reader::connectToSS(IpPortPair ss) {
	// START HERE WORK ON CONNECTING!!!!



	
	// int defaultSSPort = 3456;
	// socklen_t ClientLen;
	// struct sockaddr_in ssAddr;
	// ssAddr.sin_family = AF_INET;
	// ssAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	// ssAddr.sin_port = htons(defaultSSPort);
	// int ssPort = defaultSSPort;
	// int ssSock;

	// cout << "Connecting to server... ";
	// struct addrinfo hints, *res;
	// int sockfd;

	// memset(&hints, 0, sizeof(hints));
	// hints.ai_family = AF_UNSPEC;
	// hints.ai_socktype = SOCK_STREAM;
	// hints.ai_protocol = 6;

	// getaddrinfo(ss.getIP().c_str(), , &hints, &res);
	
	// sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);

	// if (connect(sockfd, res->ai_addr, res->ai_addrlen) < 0) {
	// 	cerr << "\nError connecting. Please try again." << endl;
	// 	v.printUsage();
	// 	exit(1);
	// }
}