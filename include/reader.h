#ifndef READER_H
#define READER_H

#include <p2.h>
#include <usage.h>
#include <chaindata.h>

class Reader {
	public:
		// Takes command line inputs and validates
		Reader(int argc, char **argv);
		~Reader();
		bool validate();
		void parseFile(string filename);

	private:
		int argc;
		char **argv;
		string CHAINFILE;
		ChainData *cd;
		Usage *u;

		bool validateURL(string url);
		bool validateOptions();
		bool doesChainFileExist(string filename);
};

#endif