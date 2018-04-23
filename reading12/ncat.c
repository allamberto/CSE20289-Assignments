#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <netdb.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>


int main(int argc, char *argv[]) {

    if(argc < 2)
      printf("Usage: ./ncat HOST PORT");

    char *HOST = argv[1];
    char *PORT = argv[2];


    struct addrinfo *results;
    struct addrinfo  hints = {
        .ai_family   = AF_UNSPEC,   /* Return IPv4 and IPv6 choices */
        .ai_socktype = SOCK_STREAM, /* Use TCP */
    };
    int status;
    if ((status = getaddrinfo(HOST, PORT, &hints, &results)) != 0) {
    	fprintf(stderr, "Could not look up %s:%s: %s\n", HOST, PORT, gai_strerror(status));
	    return EXIT_FAILURE;
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
	    fprintf(stderr, "Unable to connect to %s:%s: %s\n", HOST, PORT, strerror(errno));
    	return EXIT_FAILURE;
    }
    else
      printf("Connected to %s:%s\n", HOST, PORT);



    FILE *client_file = fdopen(client_fd, "w+");
    if (client_file == NULL) {
        fprintf(stderr, "Unable to fdopen: %s\n", strerror(errno));
        close(client_fd);
        return EXIT_FAILURE;
    }


    char buffer[BUFSIZ];
    while (fgets(buffer, BUFSIZ, stdin)) {
        fputs(buffer, client_file);
    }

    fclose(client_file);

    return EXIT_SUCCESS;
}
