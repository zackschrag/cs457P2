#include <reader.h>

Reader::Reader(int argc, char **argv) {
	Reader::argc = argc;
	Reader::argv = argv;
	Reader::CHAINFILE = "chaingang.txt";
	cd = new ChainData();
	u = new Usage();
	validate();
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

	if (argc == 2) {
		bool exist = doesChainFileExist(CHAINFILE);
		if (!exist) {
			u->printErrorAndExit("chaingang.txt does not exist.");
		}
	}
	if (argc == 4) {
		return validateOptions();
	}
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
	return true;
}

bool Reader::doesChainFileExist(string filename) {
	ifstream file(filename.c_str());
	bool good = file.good();
	file.close();
	return good;
}

void Reader::parseFile(string filename) {
	ifstream file(filename.c_str());

	string currentLine;
	string currentIP;
	int currentPort;
	getline(file, currentLine);
	/*for (unsigned int i = 0; i < currentLine.length(); i++) {
		if (!isdigit(currentLine.at(i))) {
			Usage u("Chain file is of incorrect format");
		}
	}*/
	int length = atoi(currentLine.c_str());
	int ctr = 0;

	while (ctr < length) {
		getline(file, currentLine);
		size_t pos = currentLine.find(",");
		currentIP = currentLine.substr(0,pos);
		string portString = currentLine.substr(pos+1, currentLine.length()).c_str();
		currentPort = atoi(portString.c_str());
		ctr++;
		cd->addEntry(currentIP, currentPort);
	}
	file.close();
}