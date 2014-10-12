#ifndef READER_H
#define READER_H

#include <p2.h>
#include <usage.h>
#include <chaindata.h>
#include <ss.h>

// Validates input, parses chainfile, and sends first request to stepping stone.
class Reader {
	public:
		// Takes command line inputs and validates
		Reader(int argc, char **argv);
		~Reader();
		bool validate();
		bool validateSS();
		void parseFile(string filename);
		void connectToSS();
		ChainData getChainData();
		string getChainFile();

	private:
		int argc;
		char **argv;
		string CHAINFILE;
		string url;
		ChainData *cd;
		Usage *u;

		bool validateURL(string url);
		bool validateOptions();
		bool validateOptionsSS();
		bool doesChainFileExist(string filename);
};

#endif