#include <stdio.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>

int main(int argc ,char** argv) {
    struct sockaddr_in server;
    int sock;

    sock = socket(AF_INET, SOCK_STREAM, 0);

    server.sin_family = AF_INET;
    server.sin_port = htons(12345);
    server.sin_addr.s_addr = inet_addr(argv[argc - 1]);
    bind(sock, (struct sockaddr *)&server, sizeof(server));


    connect(sock, (struct sockaddr *)&server, sizeof(server));

    while (1) {
        printf("conect\n");
        char str[8];
        printf("input: ");
        scanf("%7s", str);
        int size;
        size = send(sock, &str, sizeof(str), 0);
        if (size == -1) {
            printf("send error\n");
            break;
        }
    }


    return 0;
}
