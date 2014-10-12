#ifndef IPPORTPAIR_H
#define IPPORTPAIR_H

#include <p2.h>

// Simply to store an IP address and Port number. Convenice class
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