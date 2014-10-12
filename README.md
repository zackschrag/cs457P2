Authors: Zack Schrag, Tanner Moore
Date: October 12th, 2014

-----------------
Assumptions
-----------------
-The url argument given in the 'awget' command cannot be greater than 300 characters.
-awget arguments are given in the order in the project description: 
	awget <url> [-c chainfile]
	Example: awget www.google.com
	Example: awget www.google.com -c chain.txt

-ss arguments look like this:
	ss [-p port]
	Example: ss -p 1234 
	Example: ss

-If port is not available, the ss will select the next available port and listen on that one.

-----------------
ss
-----------------

The stepping stone will listen for connections, fulfill the request, and then go back to listening for connections. In order to exit the SS, you must '^C' to exit the program.

-The port does not open back up right away after running, so make sure that you either give the port time to reset and relaunch the stepping stones, or update the chainfile after each run with the new ports that 'ss' is listening on.

For example:
ss -p 2345
** ss fulfills request **
ss will now go back to listening, but it will be listening on port 2346 this time.

-----------------
awget
-----------------

'awget' will launch the first connection to a stepping stone, and it will also parse the chain file and construct an object from this data.

