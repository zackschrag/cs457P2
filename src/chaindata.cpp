#include <chaindata.h>

ChainData::ChainData() {
	
}

void ChainData::addEntry(string ip, string port) {
	//AddressPortTable.insert(pair<string,int>(ip, port));
	IpPortPair address(ip, port);
	AddressPortTable.push_back(address);
	SSnum++;
}

void ChainData::removeEntry(int index) {
	//AddressPortTable.
}

void ChainData::listEntries() {
	vector<IpPortPair>::iterator it;
	srand (time(NULL));
	for (it = AddressPortTable.begin(); it != AddressPortTable.end(); ++it) {
		cout << it->getIP() << " => " << it->getPort() << endl;
	}
}

IpPortPair ChainData::getRandomEntry() {
	// START HERE --> WORKING ON PULLING A RANDOM MAP ELEMENT.
	srand (time(NULL));
	sleep(0.356);
	int index = rand() % AddressPortTable.size();
	cout << "random SS: " << AddressPortTable.at(index).getIP() << endl;
	return AddressPortTable.at(index);
}