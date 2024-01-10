#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT_NUMBER 12345
#define BUFFER_SIZE 1024

int main() {
    int server_socket, client_socket;
    struct sockaddr_in server_address, client_address;
    char buffer[BUFFER_SIZE];

    // サーバーソケットの作成
    if ((server_socket = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("Error creating server socket");
        exit(EXIT_FAILURE);
    }

    // サーバーアドレスの設定
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = INADDR_ANY;
    server_address.sin_port = htons(PORT_NUMBER);

    // バインド
    if (bind(server_socket, (struct sockaddr*)&server_address, sizeof(server_address)) == -1) {
        perror("Error binding server socket");
        exit(EXIT_FAILURE);
    }

    // リッスン
    if (listen(server_socket, 5) == -1) {
        perror("Error listening for connections");
        exit(EXIT_FAILURE);
    }

    printf("Server listening on port %d...\n", PORT_NUMBER);

    // クライアントからの接続待ち
    if ((client_socket = accept(server_socket, (struct sockaddr*)&client_address, (socklen_t*)&client_address)) == -1) {
        perror("Error accepting connection");
        exit(EXIT_FAILURE);
    }

    printf("Connection accepted from %s:%d\n", inet_ntoa(client_address.sin_addr), ntohs(client_address.sin_port));

    // データの受信
    if (recv(client_socket, buffer, BUFFER_SIZE, 0) == -1) {
        perror("Error receiving data");
        exit(EXIT_FAILURE);
    }

    printf("Received data from client: %s\n", buffer);

    // ソケットのクローズ
    close(server_socket);
    close(client_socket);

    return 0;
}
