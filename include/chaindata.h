#ifndef CHAINDATA_H
#define CHAINDATA_H

#include <p2.h>
#include <ipportpair.h>

class ChainData {
	public:
		ChainData();
		void addEntry(string ip, string port);
		void removeEntry(int index);
		int getSSnum();
		void listEntries();		
		IpPortPair getRandomEntry();

	private:
		int SSnum;
		vector<IpPortPair> AddressPortTable;
};
#endif