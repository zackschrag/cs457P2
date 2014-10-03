#include <ipportpair.h>

IpPortPair::IpPortPair(string ip, string port) {
	IpPortPair::ip = ip;
	IpPortPair::port = port;
}

string IpPortPair::getIP() {
	return ip;
}

string IpPortPair::getPort() {
	return port;
}