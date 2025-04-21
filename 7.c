#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#define FIFO1 "fifo1"
#define FIFO2 "fifo2"

int main() {
    char filename[100], fileContent[3000];
    int fd1, fd2, file_fd;
    ssize_t numBytes;
    
    // Create FIFOs if they don’t exist
    mkfifo(FIFO1, 0666);
    mkfifo(FIFO2, 0666);

    printf("SERVER ONLINE\nWaiting for client request...\n");

    // Open FIFO for reading
    fd1 = open(FIFO1, O_RDONLY);
    if (fd1 == -1) {
        perror("Error opening FIFO1");
        exit(1);
    }

    // Read filename from FIFO1
    numBytes = read(fd1, filename, sizeof(filename));
    if (numBytes <= 0) {
        perror("Error reading from FIFO1");
        exit(1);
    }
    filename[numBytes] = '\0';

    // Open the requested file
    file_fd = open(filename, O_RDONLY);
    if (file_fd < 0) {
        perror("File not found");
        exit(1);
    }

    printf("Server: File '%s' found. Transferring contents...\n", filename);

    // Read file content
    numBytes = read(file_fd, fileContent, sizeof(fileContent) - 1);
    fileContent[numBytes] = '\0';

    // Send file content to client via FIFO2
    fd2 = open(FIFO2, O_WRONLY);
    write(fd2, fileContent, strlen(fileContent));

    printf("Server: File transfer completed.\n");

    // Close all file descriptors
    close(fd1);
    close(fd2);
    close(file_fd);

    return 0;
}






