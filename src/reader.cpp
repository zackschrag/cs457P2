#include <reader.h>

Reader::Reader(int argc, char **argv) {
	Reader::argc = argc;
	Reader::argv = argv;

	// Default filename
	Reader::CHAINFILE = "chaingang.txt";
	cd = new ChainData();
	u = new Usage();
}

Reader::~Reader() {
	delete cd;
	delete u;
}

bool Reader::validate() {
	// Check correct number of arguments
	if (argc != 2 && argc != 4) {
		u->printErrorAndExit("Incorrect number of arguments");
	}
	// This means user is using default filename
	if (argc == 2) {
		bool exist = doesChainFileExist(CHAINFILE);
		if (!exist) {
			u->printErrorAndExit("chaingang.txt does not exist.");
		}
	}
	if (argc == 4) {
		return validateOptions();
	}
	url = argv[1];
	return true;
}

bool Reader::validateOptions() {
	string option = (string) argv[2];
	string optionValue = (string) argv[3];

	if (option != "-c") {
		u->printErrorAndExit("");
	}

	if (optionValue.empty()) {
		u->printErrorAndExit("Please enter a filename for the '-c' option");
	}

	bool exist = doesChainFileExist(optionValue);
	if (!exist) {
		string message = optionValue + " does not exist";
		u->printErrorAndExit(message);
	}

	url = argv[1];
	CHAINFILE = optionValue;
	return true;
}

bool Reader::validateSS() {
	// Check correct number of arguments
	if (argc == 1) {
		return true;
	}
	if (argc != 3) {
		u->printErrorAndExitSS("Incorrect number of arguments");
	}
	else {
		return validateOptionsSS();
	}
	return true;
}

bool Reader::validateOptionsSS() {
	string option = (string) argv[1];
	string optionValue = (string) argv[2];

	if (option != "-p") {
		u->printErrorAndExitSS("");
	}

	if (optionValue.empty()) {
		u->printErrorAndExitSS("Please enter a valid portnumber for the '-p' option");
	}
	return true;
}

bool Reader::doesChainFileExist(string filename) {
	ifstream file(filename.c_str());
	bool good = file.good();
	file.close();
	return good;
}

ChainData Reader::getChainData() {
	return *cd;
}

string Reader::getChainFile() {
	return CHAINFILE;
}

void Reader::parseFile(string filename) {
	ifstream file(filename.c_str());

	string currentLine;
	string currentIP;
	getline(file, currentLine);
	int length = atoi(currentLine.c_str());
	int ctr = 0;

	//**** START HERE ***
	// Construct ChainData object
	while (ctr < length) {
		getline(file, currentLine);
		size_t pos = currentLine.find(" ");
		currentIP = currentLine.substr(0,pos);
		string portString = currentLine.substr(pos+1, currentLine.length()).c_str();
		ctr++;
		cd->addEntry(currentIP, portString);
	}
	file.close();
}

void Reader::connectToSS() {
	// Select random SS and request connection
	IpPortPair ssInfo = cd->getRandomEntry();
	SS ss;
	ss.client(ssInfo.getIP(), ssInfo.getPort(), url, *cd, true);
}