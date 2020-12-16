The purpose of this program is to be a web server which uses POSIX socket programming. The web server handles the following file types: HTML, JPEG, GIF, and TXT. A client connects to the server and requests a file, the web server then returns the file to the client.

The code can be compiled using the Makefile in the Template folder. The program is then run on two separate terminals. Terminal 1 runs the web server code, and terminal 2 acts as a client connecting to the server.

---------------------------------------------------------------------------------------------
The init function is run once in main and sets up a socket for receiving requests. This first creates a socket, sets up a re-use functionality to avoid timeouts, binds the socket, and listens.

accept_connection is called for each connection request. This function parses the request and returns a socket descriptor if successful. If this request should be ignore a value of -1 is returned instead of a file descriptor

get_request is called after accept_connection is successful. It receives a HTTP GET request, parses it, and copies the file path into the filename output if successful. This function returns a 0 if successful, otherwise it returns a nonzero value. Every request is printed out to the server terminal.

The return_result function is run for every successful client request. If the file exists on the server it is returned to the client along with information regarding the exchange and file. The socket is then closed. If return_result is unsuccessful in returning the file a non-zero value is returned.

return_error is run in the event that return_result is unsuccessful in returning a file to the client. Instead of returning a file, return_error creates a new text file with the filename containing a file not found message. This file not found message is returned to the client along with similar information regarding the exchange as the return_result function.
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
return_result: Collin
return_error: Hunter
Debugging: All contributed
