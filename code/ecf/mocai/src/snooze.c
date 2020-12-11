#include "csapp.h"

void handler(int sig){
    printf("Caught signal:%d\n",sig);
    return;
}

unsigned int snooze(unsigned int secs)
{
    unsigned int rs=sleep(secs);
    printf("Slept for %d of %d sec\n", secs - rs, secs);
    return 0;
}

int main(int argc, char *argv[])
{
    if(argc != 2){
        fprintf(stderr, "usage: %s <secs>\n", argv[0]);
        exit(0);
    }

    if(signal(SIGINT, handler) == SIG_ERR){
        perror("signal error\n");
    }
    (void)snooze(atoi(argv[1]));
    exit(0);
}
