#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/ioctl.h>
#include <sys/select.h>

const int thread_max = 100;
const int msg_cnt_max = 500;
const int listen_max = 100;
const int server_port = 12347;
const int buf_size = 32;

pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;

typedef struct socketThread {
  int sock;
  int cnt;
  int sock_conect;

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
  st->sock_conect = 0;
  st->cnt = 0;
  return st;
}

void *socketThreadRecv(void *arg) {

  int n;
  char buf[buf_size];

  socketThread *st = (socketThread*)arg;
  int sock0 = st->sock;
  const char *sendbuf;
  printf("client hello\n");
  printf("thread number %p\n", pthread_self());
  printf("hello sock number %d\n", sock0);

  while (1) {

    n = recv(sock0, buf, sizeof(buf), 0);

    if (n <= 0) {
      printf("client close\n"); 
      close(sock0);
      pthread_mutex_lock(&m);
      st->delthread = pthread_self();
      pthread_mutex_unlock(&m);
      break;

    }else if (st->cnt > msg_cnt_max - 1) {
      pthread_mutex_lock(&m);
      printf("thread break\n");
      st->sock_conect++;
      close(sock0);
      pthread_mutex_unlock(&m);
      break;

    }else{
      printf("client msg: %s\n", buf);
      pthread_mutex_lock(&m);
      sendbuf = "ok";
      send(sock0, sendbuf, 3, 0);
      st->cnt++;
      pthread_mutex_unlock(&m);
    }

  }

  return NULL;
}

int main() {

  int sock0;
  int cnt = 0;
  struct sockaddr_in addr;
  struct sockaddr_in client;
  socketThread *st;

  st = stInit();

  socklen_t socklen = sizeof(client);

  sock0 = socket(AF_INET, SOCK_STREAM, 0);

  addr.sin_family = AF_INET;
  addr.sin_port = htons(server_port);
  addr.sin_addr.s_addr = INADDR_ANY;

  //int val = 1;
  //ioctl(sock0, FIONBIO, &val);
  bind(sock0, (struct sockaddr *)&addr, sizeof(addr));
  listen(sock0, listen_max);

  // lockする方法を考える。
  while (1) {
    st->sock = accept(sock0, (struct sockaddr *)&client, &socklen);

    if (st->sock_conect) {
      printf("main end\n");
      break;

    }else if (st->sock > 0) {
      pthread_mutex_lock(&m);
      pthread_create(&st->thread[cnt++], NULL, socketThreadRecv, st);  
      pthread_mutex_unlock(&m);

    }else if(st->delthread) {
      printf("thread del\n");
      pthread_join(st->delthread, NULL);
      st->delthread = 0;
      cnt--;
    }

  }

  for (int i = 0; i < cnt; i++) {
    int test;
    test = pthread_join(st->thread[i], NULL);
    printf("join:%d\n", test);
  }

  printf("--- result ---\n", st->sock_conect);
  printf("sock conect%d\n", st->sock_conect);
  printf("st->delthread%p\n", st->delthread);
  printf("cnt%d\n", cnt);
  printf("st->cnt%d\n", st->cnt);

  pthread_mutex_destroy(&m);
  free(st);

  return 0;
}
