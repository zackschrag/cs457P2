#ifndef USAGE_H
#define USAGE_H

#include <p2.h>

// Prints appropriate error messages and exits
class Usage {
	public:
		Usage();
		void printUsage();
		void printUsageAndExit();
		void printErrorAndExit(string message);

		void printUsageSS();
		void printUsageAndExitSS();
		void printErrorAndExitSS(string message);
};

#endif