#ifndef CHAINDATA_H
#define CHAINDATA_H

#include <p2.h>

class ChainData {
	public:
		ChainData();
		void addEntry(string ip, int port);
		void removeEntry(int index);
		int getSSnum();
		void listEntries();		

	private:
		int SSnum;
		map<string, int> AddressPortTable;
};
#endif