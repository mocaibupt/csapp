#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h>
#include <errno.h>
#include <string.h>

typedef struct{
    int *buf;
    int n;
    int front;
    int rear;
    sem_t mutex;
    sem_t slots;
    sem_t items;
}sbuf_t;

void sbuf_init(sbuf_t *sp, int n);

void sbuf_deinit(sbuf_t *sp);

void sbuf_insert(sbuf_t *sp, int item);

int sbuf_remova(sbuf_t *sp);
