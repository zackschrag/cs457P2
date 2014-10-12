#ifndef SS_H
#define SS_H

#include <p2.h>
#include <usage.h>
#include <chaindata.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

struct packet {
	short dataLength;
	char data[300];
};

struct thread_data {
    int socket;
    int inClientSock;
    int outServerSock;
    int thread_id;
    ChainData cd;
    bool waitingOnFile;
};

struct chainPacket {
	short lastPacket;
	short ssNum;
	char port[6];
	char ip[16];
};

class SS {
	public:
		SS();
		~SS();
		void client(string ip, string port, string url, ChainData cdOrig, bool isAwget);
		void server(int port = 0);
		int clientRequestConnection(string ip, string port, ChainData cdOrig);
		int serverListen(int port);
		void receiveChainData(int servSock);
		void sendChainData(int servSock);
		void sendEmptyChainData(int servSock);
		void sendRequestPacket(packet requestPacket, int socket, string url);
		void handleRequest(int socket);

		string parseUrl(string url);

	private:
		bool waitingOnFile;
		int listenPort;
		ChainData *cd;

		int incomingClientSock;
		int outgoingServerSock;

};

#endif