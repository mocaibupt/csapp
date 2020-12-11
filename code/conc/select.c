/* $begin select */
#include "csapp.h"
void echo(int connfd);
void command(void);

int main(int argc, char **argv) 
{
    int listenfd, connfd;
    socklen_t clientlen;
    struct sockaddr_storage clientaddr;
    fd_set read_set, ready_set;
    char buffer[MAXLINE];

    if (argc != 2) {
	fprintf(stderr, "usage: %s <port>\n", argv[0]);
	exit(0);
    }
    listenfd = Open_listenfd(argv[1]);  //line:conc:select:openlistenfd

    FD_ZERO(&read_set);              /* Clear read set */ //line:conc:select:clearreadset
    FD_SET(STDIN_FILENO, &read_set); /* Add stdin to read set */ //line:conc:select:addstdin
    FD_SET(listenfd, &read_set);     /* Add listenfd to read set */ //line:conc:select:addlistenfd

    while (1) {
	    ready_set = read_set;
	    Select(listenfd+1, &ready_set, NULL, NULL, NULL); //line:conc:select:select
    	if (FD_ISSET(STDIN_FILENO, &ready_set)) //line:conc:select:stdinready
	        command(); /* Read command line from stdin */
    	if (FD_ISSET(listenfd, &ready_set)) { //line:conc:select:listenfdready
            clientlen = sizeof(struct sockaddr_storage); 
	        connfd = Accept(listenfd, (SA *)&clientaddr, &clientlen);
            memset(buffer,0,sizeof(buffer));
            int len = recv(connfd, buffer, sizeof(buffer),0);
            //客户端发送exit或者异常结束时，退出
            if(strcmp(buffer,"exit\n")==0 || len<=0)
                break;
            printf("来自客户端数据：%s\n",buffer);
            send(connfd, buffer, len, 0);
            printf("发送给客户端数据：%s\n",buffer);
	        echo(connfd); /* Echo client input until EOF */
	        Close(connfd);
	    }
    }
}

void command(void) {
    char buf[MAXLINE];
    if (!Fgets(buf, MAXLINE, stdin))
    	exit(0); /* EOF */
    printf("%s", buf); /* Process the input command */
}
/* $end select */


