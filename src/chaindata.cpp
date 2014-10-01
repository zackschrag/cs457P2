#include <chaindata.h>

ChainData::ChainData() {
	
}

void ChainData::addEntry(string ip, int port) {
	AddressPortTable.insert(pair<string,int>(ip, port));
	SSnum++;
}

void ChainData::listEntries() {
	map<string,int>::iterator it;
	for (it = AddressPortTable.begin(); it != AddressPortTable.end(); ++it) {
		cout << it->first << " => " << it->second << endl;
	}
}