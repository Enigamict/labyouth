#include "mutx.h"

pth_data PthMutexInit() {

    pth_data pth;
    pthread_mutex_init(&pth.mutex, NULL);
    pth.data = 0;
    return pth;
}

bool newThread(pthread_t *thread, void (*func), pth_data *pth) {

    int ret;
    
    ret = pthread_create(thread, NULL, func, pth);

    if (ret != 0) {
        return false;
    }

    return true;
}

int lock(pthread_mutex_t *mutx) {

    return pthread_mutex_lock(mutx);
}

int unlock(pthread_mutex_t *mutx) {

    return pthread_mutex_unlock(mutx);
}

int threadJoin(pthread_t thread) {

    return pthread_join(thread, NULL);
}

void mutexDestroy(pthread_mutex_t *mutx) {

    pthread_mutex_destroy(mutx);
}