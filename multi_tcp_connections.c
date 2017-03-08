#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#include "tcp_client.h"


int main(int argc, char **argv) {
    char *host, *port;
    int num_tcp_conns;
    int *fd_table;

    if  (argc < 2) {
        printf("Usage: %s <host> <port> <num_connections>\n", argv[0]);
        return 1;
    }

    host  = argv[1];
    port = argv[2];
    num_tcp_conns = atoi(argv[3]);

    fd_table = malloc(num_tcp_conns * sizeof(int));

    for (int x = 0; x < num_tcp_conns; x++) {
        fd_table[x] = tcp_connect(host, port);
        if (fd_table[x] < 0) {
            int error = errno;
            fprintf(stderr, "tcp_connect failed at number %d (%s)\n", x, strerror(error));
            return -1;
        }
    }

    sleep(300);
}
