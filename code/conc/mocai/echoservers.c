#include "../../include/csapp.h"

void echo(int coonfd);
void command(void);

typedef struct{
    int     maxfd;
    fd_set  read_set;
    fd_set  ready_set;
    int     nready;
    int     maxi;
    int     clientfd[FD_SETSIZE];
    int     clientrio[FD_SETSIZE];
}pool;

int byte_cnt = 0;

void init_pool(int listenfd, pool *p){
    int i;
    p->maxi = -1;
    for(i = 0; i < FD_SETSIZE; i++){
        p->clientfd[i] = -1;
    }

    p->maxi = listenfd;
    FD_ZERO(&p->read_set);
    FD_SET(listenfd, &p->read_set);
    return;
}

void add_client(int connfd, pool *p){
    int i;
    p->nready--;

    for(i = 0; i < FD_SETSIZE; i++){
        if(p->clientfd[i] < 0){
            p->clientfd[i] = connfd;
            Rio_readinitb(&p->clientrio[i], connfd);

            FD_SET(connfd, &p->read_set);

            if(connfd > p->maxfd)
                p->maxfd = connfd;

            if(i > p->maxi)
                p->maxi = i;
            break;
        }
    }
    if( i == FD_SETSIZE )
        app_error("add_client error: Too many clients\n");
}

void check_clients(pool *p){
    int i, coonfd, n;
    char buf[MAXLINE];
    rio_t rio;

    for(i = 0; i < FD_SETSIZE; i++){
        coonfd = p->clientfd[i];
        rio = p->clientrio[i];

        if((coonfd > 0) && (FD_ISSET(connfd, &p->ready_set))){
            p->nready--;

            if( (n = Rio_readlineb(&p->clientrio[i], buf, MAXLINE)) != 0 ){
                byte_cnt += n;
                printf("Server received %d(%d total) bytes on fd %d\n", n, byte_cnt, connfd);
                Rio_writen(connfd, buf, MAXLINE);
            }
            else{
                Close(coonfd);
                p->clientfd[i] = -1;
                FD_CLR(connfd, &p->read_set);
            }
        }
    }
}

int main(int argc, char *argv[])
{
    int     listenfd, connfd;
    socklen_t  clientlen;
    struct sockaddr_storage clientaddr;
    static pool pool;

    if(argc != 2){
        fprintf(stderr, "usage :%s <port>\n", argv[0]);
        exit(-1);
    }

    listenfd = open_listenfd(argv[1]);
    init_pool(listenfd, &pool);

    while(1){
        pool.ready_set = pool.read_set;
        pool.nready = Select(pool.maxfd+1, &pool.ready_set, NULL, NULL, NULL);

        if(FD_ISSET(listenfd, pool->ready_set)){
            connfd = Accept(listenfd, (struct sockaddr *)&sockaddr_storage, &clientlen);
            add_client(connfd, &pool);
        }
        check_clients(&pool);
    }
    return 0;
}

