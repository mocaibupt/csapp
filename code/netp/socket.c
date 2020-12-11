#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <error.h>


int service(char *ip, int port, int max_link){
    struct sockaddr_in local;
    int sockfd;

    if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0){
        perror("service socket fd create fail\n");
        exit(-1);
    }

    local.sin_family = AF_INET;
    inet_pton(AF_INET, ip, (char *)(&(local.sin_addr.s_addr)));
    local.sin_port = htons(port);
    socklen_t len = sizeof(local);

    if((bind(sockfd, (struct sockaddr *)(&local), len))<0){
        perror("Service socket bind failure\n");
        exit(-1);
    }
    
    if(listen(sockfd, max_link) < 0){
        perror("Service socket listen failure\n");
        exit(-1);
    }

    return 0;
}

int client()
int main(int argc, char *argv[])
{
    return 0;
}

