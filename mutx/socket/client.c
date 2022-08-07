#include <stdio.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>

int main(int argc ,char** argv) {
    struct sockaddr_in server;
    int sock;
    char buf[32];
    int n;

    sock = socket(AF_INET, SOCK_STREAM, 0);

    server.sin_family = AF_INET;
    server.sin_port = htons(12345);
    server.sin_addr.s_addr = inet_addr(argv[1]);
    bind(sock, (struct sockaddr *)&server, sizeof(server));

    while (1) {

        connect(sock, (struct sockaddr *)&server, sizeof(server));

        char str[8];
        scanf("%7s", str);
        sendto(sock, str, sizeof(char) + 7,
               0, (struct sockaddr *)&server, sizeof(server));

        memset(buf, 0, sizeof(buf));
        n = recv(sock, buf, sizeof(buf), 0);
        printf("%d, %s\n", n, buf);
    }


    return 0;
}