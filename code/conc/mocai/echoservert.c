#include "../../include/csapp.h"

void echo(int connfd);
void *thread(void *vargp);

int main(int argc, char *argv[])
{
    int listenfd, *connfd;
    socklen_t clientlen;
    struct sockaddr_storage cliendaddr;
    pthread_t tid;
    
    if(argc != 2){
        fprintf(stderr, "usage: %s <port>\n", argv[0]);
        exit(0);
    }

    listenfd = Open_listenfd(argv[1]);

    while(1){
        clientlen = sizeof(struct sockaddr_storage);
        coonfdp = Malloc(sizeof(int));
        *connfdp = Accept(listenfd, (struct sockaddr*)(&cliendaddr), clientlen);
        Pthread_create(tid, NULL, thread, connfd);
    }

    return 0;
}


void *thread(void *vargp){
    int connfd = *((int *)vargp);
    Pthread_detach(Pthread_self());
    Free(vargp);
    echo(coonfd);
    Close(coonfd);
    return NULL;
}
