#ifndef READER_H
#define READER_H

#include <p2.h>
#include <usage.h>

class Reader {
	public:
		// Takes command line inputs and validates
		Reader(int argc, char **argv);
		bool validate();

	private:
		int argc;
		char **argv;
		string CHAINFILE;

		bool validateURL(string url);
		bool validateOptions();
		bool doesChainFileExist(string filename);
};

#endif