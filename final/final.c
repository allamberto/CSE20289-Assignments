#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <netdb.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <unistd.h>

const char *HOST = "xavier.h4x0r.space";


FILE *socket_dial(const char *host, const char *port) {
    struct addrinfo *results;
    struct addrinfo  hints = {
        .ai_family   = AF_UNSPEC,   /* Return IPv4 and IPv6 choices */
        .ai_socktype = SOCK_STREAM, /* Use TCP */
    };
    int status;
    if ((status = getaddrinfo(host, port, &hints, &results)) != 0) {
    	fprintf(stderr, "getaddrinfo failed: %s\n", gai_strerror(status));
	     return NULL;
    }

    int client_fd = -1;
    for (struct addrinfo *p = results; p != NULL && client_fd < 0; p = p->ai_next) {
  	   if ((client_fd = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) < 0) {
	        fprintf(stderr, "Unable to make socket: %s\n", strerror(errno));
	        continue;
	     }

	    if (connect(client_fd, p->ai_addr, p->ai_addrlen) < 0) {
	       close(client_fd);
	       client_fd = -1;
	       continue;
	    }
    }

    freeaddrinfo(results);

    if (client_fd < 0) {
	     fprintf(stderr, "Unable to connect to %s:%s: %s\n", host, port, strerror(errno));
    	 return NULL;
    }

    FILE *client_file = fdopen(client_fd, "w+");
    if (client_file == NULL) {
        fprintf(stderr, "Unable to fdopen: %s\n", strerror(errno));
        close(client_fd);
        return NULL;
    }

    return client_file;
}

int main(int argc, char *argv[]) {
    FILE *client_file;
    char port[BUFSIZ];
    for(int i = 9500; i <= 9599; i++){
      sprintf(port, "%d", i);
      client_file = socket_dial(HOST, port);
      if(!client_file){
        continue;
      }
    }
    if(client_file == NULL){
      fprintf(stderr, "Unable to find open port: %s\n", strerror(errno));
      return EXIT_FAILURE;
    }

    struct stat st;
    stat("final.c", &st);
    int FILESIZE = st.st_size;

    /*Http request header*/
    fprintf(client_file, "PUT /alamber2 HTTP/1.0\r\n");
    fprintf(client_file, "Host: %s\n", HOST);
    fprintf(client_file, "Content-Type: text/plain\n");
    fprintf(client_file, "Content-Length: %d\n", FILESIZE);
    fprintf(client_file, "\r\n");

    /* Open source file for reading */
    FILE *file = fopen("final.c", "r");
    if (file == NULL) {
    	fprintf(stderr, "Unable to open: %s\n", strerror(errno));
    	return EXIT_FAILURE;
    }

    char buffer1[BUFSIZ];
    while(fgets(buffer1, BUFSIZ, file)){
      fputs(buffer1, client_file);
    }

    /* Copy from source to destination */
    char buffer2[FILESIZE];

    while (fgets(buffer2, FILESIZE, client_file)) {
        fputs(buffer2, stdout);
    }


    fclose(client_file);
    fclose(file);
    return EXIT_SUCCESS;
}

/* vim: set expandtab sts=4 sw=4 ts=8 ft=c: */
