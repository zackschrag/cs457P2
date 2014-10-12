#include <p2.h>
#include <reader.h>
#include <ss.h>

int main(int argc, char **argv) {
	SS ss;
	Reader r(argc, argv);
	r.validateSS();

	// string url = "http://img.izifunny.com/pics/2013/20130109/640/beautiful-nature-pictures-52-pics_37.jpg";
	// string result = ss.parseUrl(url);
	// cout << "RESULT: " << result << endl;
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