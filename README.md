The purpose of this program is to be a web server which uses POSIX socket programming. The webserver handles the following file types: HTML, JPEG, GIF, and TXT. A client connects to the server and requests a file, the web server then returns the file to the client.

The code can be compiled using the Makefile in the Template folder. The program is then run on two seperate terminals. Terminal 1 runs the web server code, and terminal 2 acts as a client connecting to the server.

---------------------------------------------------------------------------------------------
For the interim report the init, accept_connection, and get_request functions have been implemented.

The init function is run once in main and sets up a socket for recieving requests. This first creates a socket, sets up a re-use functionality to avoid timeouts, binds the socket, and listens.

accept_connection is called for each connection request. This funciton parses the request and returns a socket descripter if sucessful. If this request should be ignore a value of -1 is returned instead of a file descriptor

get_request is called after accept_connection is successful. It receives a HTTP GET request, parses it, and copies the file path into the filename output if successful. This function returns a 0 if successful, otherwise it returns a nonzero value. Every request is printed out to the server terminal.

The return_result and return_error functions have not been implemented yet and are planned to be completed for the final submission.
---------------------------------------------------------------------------------------------

Project Group: 25

Members:
Collin Campbell, camp0609
Clara Huang, huan2089
Hunter Bahl, bahlx038

Credits:
init: Collin
accept_connection: Collin
get_request: Clara
