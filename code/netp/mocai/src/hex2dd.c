#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>

int main(int argc, char *argv[]){
    struct in_addr inaddr;
    uint32_t addr;
    if(argc != 2){
        fprintf(stderr, "usage: %s <domain name>\n", argv[0]);
        exit(-1);
    }
    sscanf(argv[1], "%x", &addr);
    inaddr.s_addr = htonl(addr);
    char buf[1024];
    inet_ntop(AF_INET, &inaddr, buf, 1024);
    printf("%s\n", buf);
}

