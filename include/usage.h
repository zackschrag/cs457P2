#ifndef USAGE_H
#define USAGE_H

#include <p2.h>

class Usage {
	public:
		Usage();
		void printUsage();
		void printUsageAndExit();
		void printErrorAndExit(string message);
};

#endif