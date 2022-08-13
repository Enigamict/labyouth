#include "mutx.h"

const size_t loop_max = 65535;

void loop1(void *arg)
{
    size_t i;
    pth_data *pdata = (pth_data*)arg;

    for (i = 0; i < loop_max; i++) {
        lock(&pdata->mutex);
        pdata->data++;
        unlock(&pdata->mutex);
    }
}
 
void loop2(void *arg)
{
    size_t i;
    pth_data *pdata = (pth_data*)arg;

    for (i = 0; i < loop_max; i++) {
        lock(&pdata->mutex);
        pdata->data++;
        unlock(&pdata->mutex);
    }
}
int main() {

   pthread_t thread1, thread2;
   pth_data pth;

   pth = PthMutexInit();

   newThread(&thread1, (void *)loop1, &pth);
   newThread(&thread2, (void *)loop1, &pth);

   mutxJoin(thread1);
   mutxJoin(thread2);

   printf("pdata:%d", pth.data);
   mutexDestroy(&pth.mutex);
   return 0;
}
