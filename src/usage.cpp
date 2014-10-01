#include <usage.h>

Usage::Usage() {

}

void Usage::printUsage() {
	cerr << "Usage: awget <URL> [-c chainfile]" << endl;
}

void Usage::printUsageAndExit() {
	cerr << "Usage: awget <URL> [-c chainfile]" << endl;	
	exit(0);
}

void Usage::printErrorAndExit(string message) {
	if (message.empty()) {
		cerr << "Usage: awget <URL> [-c chainfile]" << endl;
		exit(0);
	}
	cout << "Error: " << message << endl;
	cerr << "Usage: awget <URL> [-c chainfile]" << endl;
	exit(0);
}
