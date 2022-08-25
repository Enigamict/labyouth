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

void loop3(void *arg)
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

   pthread_t thread1, thread2, thread3;
   pth_data pth;
   int test;

   pth = PthMutexInit();

   newThread(&thread1, (void *)loop1, &pth);
   printf("%p\n", thread1);
   newThread(&thread2, (void *)loop2, &pth);
   printf("%p\n", thread2);
   newThread(&thread3, (void *)loop3, &pth);
   printf("%p\n", thread3);

   test = threadJoin(thread1);
   printf("test:%d\n", test);
   threadJoin(thread2);
   threadJoin(thread3);

   printf("pdata:%d", pth.data);
   mutexDestroy(&pth.mutex);
   return 0;
}
