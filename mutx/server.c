#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main() {
 int sock0;
 struct sockaddr_in addr;
 struct sockaddr_in client;
 int len;
 int sock;
 char buf[32];
 int n;

 sock0 = socket(AF_INET, SOCK_STREAM, 0);

 addr.sin_family = AF_INET;
 addr.sin_port = htons(12345);
 addr.sin_addr.s_addr = INADDR_ANY;
 bind(sock0, (struct sockaddr *)&addr, sizeof(addr));


listen(sock0, 5);

while (1) {
    len = sizeof(client);
    sock = accept(sock0, (struct sockaddr *)&client, &len);

    char str[8];
    scanf("%7s", str);
    sendto(sock, str, sizeof(char) + 7,
           0, (struct sockaddr *)&addr, sizeof(addr));

    memset(buf, 0, sizeof(buf));
    n = recv(sock, buf, sizeof(buf), 0);
    printf("%d, %s\n", n, buf);
}



return 0;
}