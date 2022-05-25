#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>

typedef struct pth_data {
    int data;
    pthread_mutex_t mutex;
}pth_data;

int sum = 0;

void *adddata(void *arg) {
    int i;
    pth_data *pdata = (pth_data*)arg;

    for (i = 0; i < 1000000; i++) {
        pthread_mutex_lock(&pdata->mutex);
        pdata->data = sum + i;
        sum++;
        pthread_mutex_unlock(&pdata->mutex);
    }
    return NULL;
}

void *subdata(void *arg) {
    int i;
    pth_data *pdata = (pth_data*)arg;

    for (i = 0; i < 1000000; i++) {
        pthread_mutex_lock(&pdata->mutex);
        pdata->data = sum - i;
        sum--;
        pthread_mutex_unlock(&pdata->mutex);
    }
    return NULL;
}

int main() {
    pthread_t thread1;
    pthread_t thread2;
    pth_data p;

    pthread_mutex_init(&p.mutex, NULL);

    pthread_create(&thread1, NULL, &adddata, &p);
    pthread_create(&thread2, NULL, &subdata, &p);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    pthread_mutex_destroy(&p.mutex);

    printf("%d\n", p.data);
}