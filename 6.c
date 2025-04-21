#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 17000
#define BUFFER_SIZE 1024

int main() {
    int server_sock, client_sock;
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_size;
    char frame[BUFFER_SIZE], ack[BUFFER_SIZE];
    int i = 1;

    // Create socket
    server_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (server_sock == -1) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Configure server address
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    // Bind socket
    if (bind(server_sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
        perror("Binding failed");
        exit(EXIT_FAILURE);
    }

    // Listen for connections
    if (listen(server_sock, 5) == -1) {
        perror("Listening failed");
        exit(EXIT_FAILURE);
    }

    printf("Waiting for connection...\n");

    // Accept connection
    addr_size = sizeof(client_addr);
    client_sock = accept(server_sock, (struct sockaddr *)&client_addr, &addr_size);
    if (client_sock == -1) {
        perror("Connection failed");
        exit(EXIT_FAILURE);
    }

    printf("Connected to receiver.\n");

    // Send frames
    while (1) {
        printf("Enter Frame %d (type 'exit' to stop): ", i);
        scanf("%s", frame);

        send(client_sock, frame, strlen(frame), 0);
        if (strcmp(frame, "exit") == 0)
            break;

        recv(client_sock, ack, BUFFER_SIZE, 0);
        printf("Acknowledgment: %s\n", ack);

        i++;
    }

    close(client_sock);
    close(server_sock);
    return 0;
}





