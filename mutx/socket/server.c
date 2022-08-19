#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

const int thread_max = 100;

typedef struct socketThread {
  int sock;
  int cnt;
  pthread_t thread[];
}socketThread;


socketThread *stInit() {

  socketThread *st;

  st = malloc(sizeof(socketThread) + sizeof(pthread_t) * thread_max);

  if (st == NULL) {
      return NULL;
  }

  st->cnt = 0;
  st->sock = 0;
  return st;
}


void *socketThreadRecv(void *arg) {

  int n;
  char buf[32];
  socketThread *st = (socketThread*)arg;

  while (1) {
    n = recv(st->sock, buf, sizeof(buf), 0);
    if (n == 0 || strcmp(buf, "exit") == 0) {
      printf("client close\n"); 
      close(st->sock);
      st->cnt--;
      pthread_detach(pthread_self());
      break;
    }
    printf("%d, %s\n", n, buf);
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
  bind(sock0, (struct sockaddr *)&addr, sizeof(addr));

  listen(sock0, 5);

  while (1){
    printf("connect\n");
    st->sock = accept(sock0, (struct sockaddr *)&client, &socklen);
    pthread_create(&st->thread[st->cnt++], NULL, socketThreadRecv, st);
  }

  return 0;
}
