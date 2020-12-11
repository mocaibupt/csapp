#include <stdio.h>
#include <arpa/inet.h>
#include <sys/unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdlib.h>
#include <string.h>

#define MAXLINE 1025

int open_client(char *hostname, char *port){
    struct addrinfo hints, *listp, *p;
    int clientfd;

    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_NUMERICSERV | AI_ADDRCONFIG;
    if(getaddrinfo(hostname, port, &hints, &listp) != 0){
        fprintf(stderr, "getaddrinfo error in openclient(%s,%s)\n",hostname, port);
    }

    for(p = listp; p != NULL; p = p->ai_next){
        if(clientfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol) < 0)
            continue;

        if(connect(clientfd, p->ai_addr, p->ai_addrlen) != -1)
            break;
        close(clientfd);
    }

    free(listp);
    if( !p )
        return -1;
    else
        return clientfd;

}

int main(int argc, char *argv[])
{
    int clientfd;
    char *host, *port, buf[MAXLINE];
    
    if(argc != 3){
        fprintf(stderr, "usage :%s <host><port>\n", argv[0]);
        exit(-1);
    }

    host = argv[1];
    port = argv[2];

    open_client(host, port);

    return 0;
}

