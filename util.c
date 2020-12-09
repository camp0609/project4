#ifndef _REENTRANT
#define _REENTRANT
#endif

#include <stdio.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "util.h"

#define BACKLOG 20
#define MSGSIZE 2048

//global socket ?
int sockfd;
/**********************************************
 * init
   - port is the number of the port you want the server to be
     started on
   - initializes the connection acception/handling system
   - YOU MUST CALL THIS EXACTLY ONCE (not once per thread,
     but exactly one time, in the main thread of your program)
     BEFORE USING ANY OF THE FUNCTIONS BELOW
   - if init encounters any errors, it will call exit().
************************************************/
void init(int port) {
  struct sockaddr_in serv_addr;
  int addr_size;
  serv_addr.sin_family = AF_INET;  
  serv_addr.sin_port = htons(port);  
  serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
  
  //create socket
  if ((sockfd = socket(PF_INET, SOCK_STREAM, 0)) == -1) {    
    perror("Can't create socket");    
    exit(1);  
  }

  //set re-use so do not need to wait for standard timeout if we shut-down or restart 
  if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int)) == -1) {    
    perror("Can't set socket option");    
    exit(1);  
  }

  //bind socket 
  if (bind(sockfd, (struct sockaddr *)&my_addr, sizeof(my_addr)) == -1) {    
    perror("Could not bind");    
    exit(1);  
  }

  if (listen(sockfd, BACKLOG) == -1) {    
    perror("Could not listen");    
    exit(1);  
  }
}

/**********************************************
 * accept_connection - takes no parameters
   - returns a file descriptor for further request processing.
     DO NOT use the file descriptor on your own -- use
     get_request() instead.
   - if the return value is negative, the request should be ignored.
***********************************************/
int accept_connection(void) {
  int client_fd;
  struct sockaddr_in client_addr;
  addr_size = sizeof(client_addr);
  if ((client_fd = accept(sockfd, (struct sockaddr *)&client_addr, &addr_size)) == -1) {      
    perror("Failed to accept connection");      
    continue;    
  }
  return client_fd;
}

/**********************************************
 * get_request
   - parameters:
      - fd is the file descriptor obtained by accept_connection()
        from where you wish to get a request
      - filename is the location of a character buffer in which
        this function should store the requested filename. (Buffer
        should be of size 1024 bytes.)
   - returns 0 on success, nonzero on failure. You must account
     for failures because some connections might send faulty
     requests. This is a recoverable error - you must not exit
     inside the thread that called get_request. After an error, you
     must NOT use a return_request or return_error function for that
     specific 'connection'.
************************************************/
int get_request(int fd, char *filename) {
  //this isnt right 
  char msg[MSGSIZE];    
  int readsz = 0;    
  if ((readsz = read(fd, msg, MSGSIZE-1)) >= 0) {      
    msg[readsz] = '\0';      
    fprintf(stderr, "Client sez %s", msg);    
  }
}

/**********************************************
 * return_result
   - returns the contents of a file to the requesting client
   - parameters:
      - fd is the file descriptor obtained by accept_connection()
        to where you wish to return the result of a request
      - content_type is a pointer to a string that indicates the
        type of content being returned. possible types include
        "text/html", "text/plain", "image/gif", "image/jpeg" cor-
        responding to .html, .txt, .gif, .jpg files.
      - buf is a pointer to a memory location where the requested
        file has been read into memory (the heap). return_result
        will use this memory location to return the result to the
        user. (remember to use -D_REENTRANT for CFLAGS.) you may
        safely deallocate the memory after the call to
        return_result (if it will not be cached).
      - numbytes is the number of bytes the file takes up in buf
   - returns 0 on success, nonzero on failure.
************************************************/
int return_result(int fd, char *content_type, char *buf, int numbytes) {
}

/**********************************************
 * return_error
   - returns an error message in response to a bad request
   - parameters:
      - fd is the file descriptor obtained by accept_connection()
        to where you wish to return the error
      - buf is a pointer to the location of the error text
   - returns 0 on success, nonzero on failure.
************************************************/
int return_error(int fd, char *buf) {
}
