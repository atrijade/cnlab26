#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

#define SERVER_IP "127.0.0.1"
#define PORT 8080
#define BUFFER_SIZE 1024

int main() {
    int sockfd;
    struct sockaddr_in server_addr;
    socklen_t addr_len;
    char buffer[BUFFER_SIZE];

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = inet_addr(SERVER_IP);

    printf("Enter filename to request: ");
    fgets(buffer, BUFFER_SIZE, stdin);
    buffer[strcspn(buffer, "\n")] = 0; // Remove newline

    sendto(sockfd, buffer, strlen(buffer), 0, 
          (struct sockaddr*)&server_addr, sizeof(server_addr));

    printf("Waiting for file contents...\n");

    addr_len = sizeof(server_addr);
    while (1) {
        int bytes_received = recvfrom(sockfd, buffer, BUFFER_SIZE, 0, 
                                     (struct sockaddr*)&server_addr, &addr_len);
        if (bytes_received < 0) {
            perror("Error receiving file");
            break;
        }
        buffer[bytes_received] = '\0';

        if (strcmp(buffer, "END") == 0) break;
        printf("%s", buffer);
    }

    printf("\nFile transfer complete.\n");
    close(sockfd);
    return 0;
}
