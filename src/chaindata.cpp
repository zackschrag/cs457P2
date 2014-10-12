#include <chaindata.h>

ChainData::ChainData() {
	SSnum = 0;
}

int ChainData::getSSnum() {
	return SSnum;
}

void ChainData::setSSnum(int newNum) {
	SSnum = newNum;
}

void ChainData::addEntry(string ip, string port) {
	IpPortPair address(ip, port);
	AddressPortTable.push_back(address);
	SSnum++;
}

void ChainData::removeEntry(int index) {
	vector<IpPortPair>::iterator pos = AddressPortTable.begin()+index;
	AddressPortTable.erase(pos);
	SSnum--;
}

IpPortPair ChainData::getEntry(int index) {
	return AddressPortTable.at(index);
}

void ChainData::listEntries() {
	vector<IpPortPair>::iterator it;
	srand (time(NULL));
	cout << "\tchainlist is ";
	if (SSnum == 0) {
		cout << "empty" << endl;
	}
	else {
		cout << endl;
		for (it = AddressPortTable.begin(); it != AddressPortTable.end(); ++it) {
			cout << "\t" << it->getIP() << ", " << it->getPort() << endl;
		}
	}
}

IpPortPair ChainData::getRandomEntry() {
	srand (time(NULL));
	sleep(0.356);
	int index = rand() % AddressPortTable.size();
	cout << "\tnext SS is " << AddressPortTable.at(index).getIP() << ", " << AddressPortTable.at(index).getPort() << endl;
	IpPortPair result = AddressPortTable.at(index);
	removeEntry(index);
	return result;
}

void ChainData::clearAllData() {
	int ctr = SSnum;
	for (int i = 0; i < ctr; i++) {
		removeEntry(i);
	}
}