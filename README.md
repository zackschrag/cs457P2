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

-----------------
awget
-----------------


