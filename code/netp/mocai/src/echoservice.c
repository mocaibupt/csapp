#include <stdio.h>
#include <arpa/inet.h>
#include <sys/unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdlib.h>
#include <string.h>

#define LISTENQ 12
#define MAXLINE 1024

int open_listed(char *port){
    struct addrinfo hints, *listp, *p;
    int listenfd, optval = 1;

    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_NUMERICSERV | AI_ADDRCONFIG;
    hints.ai_flags |= AI_PASSIVE;
    if(getaddrinfo(NULL, port, &hints, &listp) != 0){
        fprintf(stderr, "getaddrinfo error in open_listed(%s)\n", port);
    }

    for(p = listp; p != NULL; p = p->ai_next){
        if(listenfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol) < 0)
            continue;

        setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, (const void *)&optval, sizeof(int));
        
        if(bind(listenfd, p->ai_addr, p->ai_addrlen) != -1)
            break;
        close(listenfd);
    }

    free(listp);
    if( !p )
        return -1;

    if(listen(listenfd, LISTENQ) < 0){
        close(listenfd);
        return -1;
    }
    return listenfd;

}

int main(int argc, char *argv[])
{
    int listenfd, connfd;
    socklen_t clientlen;
    struct sockaddr_storage clientaddr;
    char client_hostname[MAXLINE], client_port[MAXLINE];

    if(argc != 2){
        fprintf(stderr, "usage :%s <port>\n", argv[0]);
        exit(-1);
    }

    listenfd = open_listed(argv[1]);
    while(1){
        clientlen = sizeof(struct sockaddr_storage);
        connfd = accept(listenfd, (struct sockaddr*)&clientaddr, &clientlen);
        getnameinfo((struct sockaddr *)clientaddr, clientlen, client_hostname, MAXLINE, client_port, MAXLINE,0);
        printf("Connected to (%s, %s)\n", client_hostname, client_port);
        echo(connfd);
        close(connfd);
    }

    return 0;
}

