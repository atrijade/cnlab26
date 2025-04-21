#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

#define PORT 8080
#define BUFFER_SIZE 1024

int main() {
    int sockfd;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_len;
    char buffer[BUFFER_SIZE];

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    if (bind(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("Binding failed");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    printf("Server listening on port %d...\n", PORT);
    
    client_len = sizeof(client_addr);

    // Receive filename (FIX: Capture bytes received and null-terminate)
    ssize_t num_bytes = recvfrom(sockfd, buffer, BUFFER_SIZE - 1, 0, 
                                 (struct sockaddr*)&client_addr, &client_len);
    if (num_bytes < 0) {
        perror("Error receiving filename");
        close(sockfd);
        exit(EXIT_FAILURE);
    }
    buffer[num_bytes] = '\0'; // Proper null-termination

    printf("Client requested file: %s\n", buffer);
    ssize_t numBytes;
    int file = open(buffer, O_RDONLY);
    if (!file) {
        perror("File not found");
        sendto(sockfd, "ERROR: File not found", 22, 0, 
              (struct sockaddr*)&client_addr, client_len);
    } else {
        numBytes = read(file, buffer, BUFFER_SIZE) ;
            sendto(sockfd, buffer, strlen(buffer), 0, 
                  (struct sockaddr*)&client_addr, client_len);
        
        sendto(sockfd, "END", 3, 0, 
              (struct sockaddr*)&client_addr, client_len);
        printf("File sent successfully.\n");
        close(file);
    }

    close(sockfd);
    return 0;
}
