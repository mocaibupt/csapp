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
    inet_pton(AF_INET, argv[1], &addr);
    printf("%x\n", ntohl(addr));
    return 0;
}

