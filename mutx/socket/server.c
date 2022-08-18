#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

void *socketThreadRecv(void *arg) {

  int n;
  int sock0 = *(int *)arg;
  char buf[32];

  while (1) {
    n = recv(sock0, buf, sizeof(buf), 0);
    if (n == 0) {
      printf("client close\n"); 
      close(sock0);
      break;
    }
    printf("%d, %s\n", n, buf);
  }

  return NULL;

}

int main() {
  int sock0;
  int sock;
  struct sockaddr_in addr;
  struct sockaddr_in client;
  pthread_t thread;

  socklen_t socklen = sizeof(client);

  sock0 = socket(AF_INET, SOCK_STREAM, 0);

  addr.sin_family = AF_INET;
  addr.sin_port = htons(12345);
  addr.sin_addr.s_addr = INADDR_ANY;
  bind(sock0, (struct sockaddr *)&addr, sizeof(addr));

  listen(sock0, 5);

  while (1){
    printf("connect\n");
    sock = accept(sock0, (struct sockaddr *)&client, &socklen);
    pthread_create(&thread, NULL, socketThreadRecv, (void *)&sock);
  }

  return 0;
}
