#include <p2.h>
#include <reader.h>
#include <ss.h>

int main(int argc, char **argv) {
	SS ss;
	Reader r(argc, argv);
	r.validateSS();

	// Start listening for requests
	if (argc > 1) {
		string port = argv[2];
		ss.server(atoi(port.c_str()));
	}
	else {
		// List on default port
		ss.server();
	}
	return 0;
}