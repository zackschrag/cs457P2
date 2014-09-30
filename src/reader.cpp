#include <reader.h>

Reader::Reader(int argc, char **argv) {
	Reader::argc = argc;
	Reader::argv = argv;
	Reader::CHAINFILE = "chaingang.txt";
	validate();
}

bool Reader::validate() {
	// Check correct number of arguments
	if (argc != 2 && argc != 4) {
		Usage u("Incorrect number of arguments");
	}

	if (argc == 2) {
		bool exist = doesChainFileExist(CHAINFILE);
		if (!exist) {
			Usage u("chaingang.txt does not exist.");
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
		Usage u("");
	}

	if (optionValue.empty()) {
		Usage u("Please enter a filename for the '-c' option");
	}

	bool exist = doesChainFileExist(optionValue);
	if (!exist) {
		string message = optionValue + " does not exist";
		Usage u(message);
	}
	return true;
}

bool Reader::doesChainFileExist(string filename) {
	ifstream file(filename.c_str());
	return file.good();
}