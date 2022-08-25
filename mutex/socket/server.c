#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/ioctl.h>

const int thread_max = 100;
pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;

typedef struct socketThread {
  int sock;
  int cnt;
  int data;
  pthread_t delthread;
  pthread_t thread[];
}socketThread;


socketThread *stInit() {

  socketThread *st;

  st = malloc(sizeof(socketThread) + sizeof(pthread_t) * thread_max);

  if (st == NULL) {
      return NULL;
  }

  st->delthread = 0;
  st->cnt = 0;
  st->data = 0;
  return st;
}

void *socketThreadRecv(void *arg) {

  int n = 1;
  char buf[32];
  socketThread *st = (socketThread*)arg;
  int sock0 = st->sock;
  int data;
  char *sendbuf;
  printf("client hello\n");
  printf("%d", sock0);
  printf("thread number %p\n", pthread_self());

  while (1) {
    printf("count data:%d\n", st->data);

    n = recv(sock0, buf, sizeof(buf), 0);
    data = st->data;

    if (data > 9) {
      printf("saisaku syori\n"); 
      break;
    }

    if (n <= 0) {
      printf("client close\n"); 
      close(sock0);
      st->delthread = pthread_self();
      break;
    }else{
      st->data++;
      sendbuf = "a";
      send(sock0, sendbuf, sizeof(char) + 1, 0);

      printf("%d, %s\n", n, buf);
    }

  }

  return NULL;
}

int main() {
  int sock0;
  int sock_list[10];
  struct sockaddr_in addr;
  struct sockaddr_in client;
  socketThread *st;
  char *sendbuf;

  st = stInit();

  socklen_t socklen = sizeof(client);

  sock0 = socket(AF_INET, SOCK_STREAM, 0);

  addr.sin_family = AF_INET;
  addr.sin_port = htons(12345);
  addr.sin_addr.s_addr = INADDR_ANY;

  int val = 1;
  int count;
  ioctl(sock0, FIONBIO, &val);
  bind(sock0, (struct sockaddr *)&addr, sizeof(addr));
  listen(sock0, 5);

  while (1) {
    st->sock = accept(sock0, (struct sockaddr *)&client, &socklen);

    if (st->sock > 0) {
      pthread_create(&st->thread[st->cnt++], NULL, socketThreadRecv, st); 
      count = st->cnt - 1;
      sock_list[count] = st->sock;

    }else if (st->data == 10) {
      printf("main break\n");
      sendbuf = "end";
      for (int i = 0; i < st->cnt; i++) {
        send(sock_list[i], sendbuf, sizeof(char) + 3, 0);
        close(sock_list[i]);
      }

      break;

    }else if(st->delthread) {
      printf("thread del\n");
      pthread_join(st->delthread, NULL);
      st->delthread = 0;
      st->cnt--;
    } 
  }

  for (int i = 0; i < st->cnt; i++) {
    printf("thread join\n");
    int test;
    test = pthread_join(st->thread[i], NULL);
    printf("join:%d\n", test);
  }

  free(st);

  return 0;
}
