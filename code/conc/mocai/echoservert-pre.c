#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netdb.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>

#include "sbuf.h"

#define NTHREADS 4
#define SUBFSIZE 16

void echo_cnt(int connfd);
void *thread(void *vargp);

sbuf_t sbuf;

int main(int argc, char *argv[])
{
    int i, listenfd, connfd, rc, optval = 1;
    struct addrinfo hints, *listp, *p;
    struct sockaddr_storage clientaddr;
    socklen_t clientlen;
    pthread_t tid;

    if(argc != 2){
        fprintf(stderr, "usage : %s <port>\n", argv[0]);
        exit(0);
    }
    
    
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE | AI_ADDRCONFIG | AI_NUMERICSERV;
    if( (i = getaddrinfo(NULL, argv[1], &hints, &listp)) != 0 ){
        fprintf(stderr, "getaddrinfo failure(port = %s)(error = %s)\n", argv[1], gai_strerror(i));
        return -2;
    }

    for( p =listp; p ; p = p->ai_next ){
        if((listenfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) < 0){
            continue;
        }

        /* Eliminates "Address already in use" error from bind */                                                               
        setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR,    //line:netp:csapp:setsockopt
                  (const void *)&optval , sizeof(int));


        if((bind( listenfd, (struct sockaddr*)p->ai_addr), p->ai_addrlen) == 0)
            break;
        
        if(close(listenfd) < 0){
           fprintf(stderr, "close(listenfd) failure:%s\n", strerror(errno));
           return -1;
        }
    }

    freeaddrinfo(listp);
    if(!p)
        return -1;

    if(listen(listenfd, 5) < 0){
        close(listenfd);
        return -1;
    }

    sbuf_init(&subf, SUBFSIZE);
    for(i = 0; i < NTHREADS; i++){
        if((rc = pthread_create(&tid, NULL, thread, NULL)) != 0)
            fprintf(stderr, "pthread_create failure (error code = %d)", rc);
    }

    while(1){
        clientlen = sizeof(struct sockaddr_storage);
        if((clientlen = accept(listenfd, (struct sockaddr *)&clientaddr, &clientlen)) < 0)
            fprintf(stderr, "accept error");
        sbuf_insert(&sbuf, connfd);
    }

    return 0;
}

void *thread(void *vargp){
    int rc;
    if((rc = pthread_detach(pthread_self())) != 0)
        fprintf(stderr, "phtread_detach error %s", strerror(rc));
    while(1){
        int connfd = sbuf_remove(&sbuf);
        echo_cnt(connfd);
        if( close(connfd) != 0)
            fprintf(stderr, "close(connfd) error: %s\n", strerror(errno));

    }
}

