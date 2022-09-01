#include <stdio.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>


int main(int argc ,char** argv) {
    struct sockaddr_in server;
    int sock;
    char buf[32];
    char str[32];
    int n = 0;

    sock = socket(AF_INET, SOCK_STREAM, 0);

    server.sin_family = AF_INET;
    server.sin_port = htons(12347);
    server.sin_addr.s_addr = inet_addr(argv[argc - 1]);
    bind(sock, (struct sockaddr *)&server, sizeof(server));

    connect(sock, (struct sockaddr *)&server, sizeof(server));

    strcpy(str,"hello");

    while (1) {
        printf("conect\n");
        int size;
        size = send(sock, &str, sizeof(str), 0);
        if (size == -1) {
            printf("send error\n");
            break;
        }
        n = recv(sock, buf, sizeof(buf), 0);
        printf("%d, %s\n", n, buf);
        if (strcmp(buf ,"end") == 0) {
            break;
        }
        sleep(1);
    }

    close(sock);


    return 0;
}
