#include <mutx.h>

pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;
const size_t loop_max = 65535;
int count;

void f1()
{
    size_t i;

    for (i = 0; i < loop_max; i++) {
        pthread_mutex_lock(&m);
        count++;
        pthread_mutex_unlock(&m);
    }
}
 
void f2()
{
    size_t i;

    for (i = 0; i < loop_max; i++) {
        pthread_mutex_lock(&m);
        count++;
        pthread_mutex_unlock(&m);
    }
}
int main() {
   // pthread_t thread1;
   // pthread_t thread2;
   // pth_data p;

   // pthread_mutex_init(&p.mutex, NULL);

   // pthread_create(&thread1, NULL, &adddata, &p);
   // pthread_create(&thread2, NULL, &subdata, &p);

   // pthread_join(thread1, NULL);
   // pthread_join(thread2, NULL);

   // pthread_mutex_destroy(&p.mutex);

   // printf("%d\n", p.data);

   pthread_t thread1, thread2;

   pthread_create(&thread1, NULL, (void *)f1, NULL);
   pthread_create(&thread2, NULL, (void *)f2, NULL);
   pthread_join(thread1,NULL);
   pthread_join(thread2,NULL);
   printf("%d", count);
   pthread_mutex_destroy(&m);
   return 0;
}
