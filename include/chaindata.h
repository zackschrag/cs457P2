#ifndef CHAINDATA_H
#define CHAINDATA_H

#include <p2.h>
#include <ipportpair.h>

class ChainData {
	public:
		ChainData();
		void addEntry(string ip, string port);
		void removeEntry(int index);
		IpPortPair getEntry(int index);
		int getSSnum();
		void setSSnum(int newNum);
		void listEntries();		
		IpPortPair getRandomEntry();
		void clearAllData();
		vector<IpPortPair> AddressPortTable;

	private:
		int SSnum;
};
#endif