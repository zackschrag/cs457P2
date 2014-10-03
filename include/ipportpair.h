#ifndef IPPORTPAIR_H
#define IPPORTPAIR_H

#include <p2.h>

class IpPortPair {
public:
	IpPortPair(string ip, string port);
	string getPort();
	string getIP();

private:
	string ip;
	string port;

};

#endif