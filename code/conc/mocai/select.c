#include "/home/mocai/CS/code/include/csapp.h"

void echo(int connfd);
void command(void);

int main(int argc, char *argv[]){
    int listenfd, connfd;
    socklen_t clientlen;
    struct sockaddr_storage clientaddr;
    fd_set read_set, ready_set;

    FD_ZERO(read_set);
    FD_SET(STDIN_FILENO, read_set);
    FD_SET(listenfd, read_set);

    while(1){
        ready_set = read_set;
        select(listenfd+1, )
    }
}
