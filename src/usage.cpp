#include <usage.h>

Usage::Usage(string message) {
	if (message.empty()) {
		cerr << "Usage: awget <URL> [-c chainfile]" << endl;
		exit(-1);
	}
	cout << message << endl;
	cerr << "Usage: awget <URL> [-c chainfile]" << endl;
	exit(-1);
}
