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
  st->sock = 0;
  return st;
}

void *socketThreadRecv(void *arg) {

  int n;
  char buf[32];
  socketThread *st = (socketThread*)arg;
  int sock0 = st->sock;
  printf("client hello\n");
  printf("thread number %p\n", pthread_self());

  while (1) {
    n = recv(sock0, buf, sizeof(buf), 0);

    if (n <= 0) {
      printf("client close\n"); 
      close(sock0);
      st->delthread = pthread_self();
      break;

    }else if (st->data == 10){
      printf("data max\n"); 
      close(sock0);
      break;

    }else{
      st->data++;
      printf("data:%d\n", st->data);

      printf("%d, %s\n", n, buf);
    }

  }

  return NULL;
}

int main() {
  int sock0;
  struct sockaddr_in addr;
  struct sockaddr_in client;
  socketThread *st;

  st = stInit();

  socklen_t socklen = sizeof(client);

  sock0 = socket(AF_INET, SOCK_STREAM, 0);

  addr.sin_family = AF_INET;
  addr.sin_port = htons(12345);
  addr.sin_addr.s_addr = INADDR_ANY;

  int val = 1;
  ioctl(sock0, FIONBIO, &val);
  bind(sock0, (struct sockaddr *)&addr, sizeof(addr));
  listen(sock0, 5);

  while (1) {
    st->sock = accept(sock0, (struct sockaddr *)&client, &socklen);

    if (st->sock > 0) {
      pthread_create(&st->thread[st->cnt++], NULL, socketThreadRecv, st); 

    }else if (st->data == 10) {
      printf("break\n");
      break;

    }else if(st->delthread) {
      printf("thread del\n");
      pthread_join(st->delthread, NULL);
      st->delthread = 0;
      st->cnt--;
    } 
  }

  for (int i = 0; i < st->cnt; i++) {
    pthread_join(st->thread[i], NULL);
  }

  free(st);

  return 0;
}
