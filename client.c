#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define SERVER_IP "127.0.0.1"
#define PORT_NUMBER 12345
#define BUFFER_SIZE 1024

int main() {
    int client_socket;
    struct sockaddr_in server_address;
    char buffer[BUFFER_SIZE];

    // クライアントソケットの作成
    if ((client_socket = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("Error creating client socket");
        exit(EXIT_FAILURE);
    }

    // サーバーアドレスの設定
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = inet_addr(SERVER_IP);
    server_address.sin_port = htons(PORT_NUMBER);

    // サーバーに接続
    if (connect(client_socket, (struct sockaddr*)&server_address, sizeof(server_address)) == -1) {
        perror("Error connecting to server");
        exit(EXIT_FAILURE);
    }

    printf("Connected to server on %s:%d\n", SERVER_IP, PORT_NUMBER);

    // データの送信
    char message[] = "Hello, server!";
    if (send(client_socket, message, strlen(message), 0) == -1) {
        perror("Error sending data");
        exit(EXIT_FAILURE);
    }

    printf("Data sent to server: %s\n", message);

    // ソケットのクローズ
    close(client_socket);

    return 0;
}
