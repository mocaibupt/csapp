#include "csapp.h"

void mmapcopy(int fd, int size){
    char *bufp;

    bufp = Mmap(NULL, size, PROT_READ, MAP_PRIVATE, fd, 0);
    write(1, bufp, size);
    return;
}

int main(int argc, char *argv[])
{
    struct stat stat;
    int fd;

    if(argc != 2){
        printf("usage: %s <filename>\n",argv[0]);
        exit(0);
    }

    fd = Open(argv[1], O_RDONLY, 0);
    fstat(fd, &stat);
    printf("the size of %s :%ld\n", argv[1], stat.st_size);
    mmapcopy(fd, stat.st_size);

    
    return 0;
}

