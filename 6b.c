
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 17000
#define BUFFER_SIZE 1024

int main() {
    int sock;
    struct sockaddr_in server_addr;
    char frame[BUFFER_SIZE], ack[BUFFER_SIZE];
    int i = 1;

    // Create socket
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == -1) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Configure server address
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    // Connect to server
    if (connect(sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
        perror("Connection failed");
        exit(EXIT_FAILURE);
    }

    printf("Connected to sender.\n");

    // Receive frames
    while (1) {
        recv(sock, frame, BUFFER_SIZE, 0);
        frame[strlen(frame)] = '\0';

        if (strcmp(frame, "exit") == 0)
            break;

        printf("Frame %d received: %s\n", i, frame);

        // Send acknowledgment
        strcpy(ack, "ACK");
        send(sock, ack, strlen(ack), 0);

        i++;
    }

    close(sock);
    return 0;
}
