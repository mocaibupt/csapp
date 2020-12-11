/* 
 * badcnt.c - An improperly synchronized counter program 
 */
/* $begin badcnt */
/* WARNING: This code is buggy! */
#include <stdio.h>
#include <semaphore.h>
#include <pthread.h>
#include <stdlib.h>


void *thread(void *vargp);  /* Thread routine prototype */

/* Global shared variable */
volatile long cnt = 0; /* Counter */
sem_t *mutexp;

int main(int argc, char **argv) 
{
    long niters;
    pthread_t tid1, tid2;
    sem_t mutex;
    mutexp= &mutex;

    /* Check input argument */
    if (argc != 2) { 
	    printf("usage: %s <niters>\n", argv[0]);
	    exit(0);
    }

    niters = atoi(argv[1]);
    
    sem_init(&mutex, 0, 1);

    /* Create threads and wait for them to finish */
    pthread_create(&tid1, NULL, thread, &niters);
    pthread_create(&tid2, NULL, thread, &niters);
    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);

    /* Check result */
    if (cnt != (2 * niters))
	   printf("BOOM! cnt=%ld\n", cnt);
    else
	   printf("OK cnt=%ld\n", cnt);
    exit(0);
}

/* Thread routine */
void *thread(void *vargp) 
{
    long i, niters = *((long *)vargp);

    for (i = 0; i < niters; i++) //line:conc:badcnt:beginloop
    {   
        sem_wait(mutexp);
        cnt++;                   //line:conc:badcnt:endloop
        sem_post(mutexp);
    }

    return NULL;
}
/* $end badcnt */

