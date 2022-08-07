#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#include <err.h>
#include <unistd.h>

typedef struct pth_data {
    int data;
    pthread_mutex_t mutex;
}pth_data;

int mutxIint(void *arg);
void *adddata(void *arg);
void *subdata(void *arg);