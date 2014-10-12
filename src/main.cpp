#include <p2.h>
#include <reader.h>

int main(int argc, char **argv) {
	Reader r(argc, argv);
	r.validate();

	// Now we know all arguments are valid
	//Parse chainfile and construct ChainData object
	cout << "r.getChainFile() -- " << r.getChainFile() << endl;
	r.parseFile(r.getChainFile());

	cout << "awget:" << endl;
	cout << "\tRequest: " << argv[1] << endl;
	ChainData cd = r.getChainData();
	cd.listEntries();

	// Initialize request to SS
	r.connectToSS();
}