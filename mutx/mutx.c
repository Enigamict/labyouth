#include <mutx.h>

typedef struct pth_data {
    int data;
    pthread_mutex_t mutex;
}pth_data;

int sum = 0;

// boolに変更する, それかこの中でエラーを出す
int mutexInit(struct pth_data *pth) {

    pthread_mutex_init(&pth->mutex, NULL);
}

int lock(struct pth_data *pth) {

    pthread_mutex_lock(&pth->mutex);
}

int unlock(struct pth_data *pth) {

    pthread_mutex_unlock(&pth->mutex);
}

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