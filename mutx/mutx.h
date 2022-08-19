#pragma once

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>
#include <err.h>
#include <unistd.h>

typedef struct pth_data {
    int data;
    pthread_mutex_t mutex;
}pth_data;

pth_data PthMutexInit();
bool newThread(pthread_t *thread, void (*func), pth_data *pth);
int lock(pthread_mutex_t *mutx);
int unlock(pthread_mutex_t *mutx);
int threadJoin(pthread_t thread);
void mutexDestroy(pthread_mutex_t *mutx);