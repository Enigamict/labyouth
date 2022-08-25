#include "mutx.h"

void change1(void *arg)
{
    pth_data *pdata = (pth_data*)arg;

    lock(&pdata->mutex);
    pdata->data = 10;
    unlock(&pdata->mutex);
}
 
void change2(void *arg)
{
    pth_data *pdata = (pth_data*)arg;

    lock(&pdata->mutex);
    pdata->data = 11;
    unlock(&pdata->mutex);
}

int main() {

   pthread_t thread1, thread2;
   pth_data pth;

   pth = PthMutexInit();

   newThread(&thread1, (void *)change1, &pth);
   newThread(&thread2, (void *)change2, &pth);
   mutxJoin(thread1);
   mutxJoin(thread2);


   printf("pdata:%d", pth.data);
   mutexDestroy(&pth.mutex);
   return 0;
}