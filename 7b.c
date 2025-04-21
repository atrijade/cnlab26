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
    int fd1, fd2;
    ssize_t numBytes;

    printf("Waiting for server...\n");

    // Open FIFO1 for writing
    fd1 = open(FIFO1, O_WRONLY);
    if (fd1 == -1) {
        perror("Error opening FIFO1");
        exit(1);
    }

    // Get the filename from user
    printf("SERVER ONLINE!\nEnter the filename: ");
    scanf("%s",filename);
    
    // Send filename to server
    write(fd1, filename, strlen(filename));

    // Open FIFO2 for reading
    fd2 = open(FIFO2, O_RDONLY);
    if (fd2 == -1) {
        perror("Error opening FIFO2");
        exit(1);
    }

    // Read file contents from server
    numBytes = read(fd2, fileContent, sizeof(fileContent) - 1);
    fileContent[numBytes] = '\0';

    printf("File received! Displaying contents:\n%s\n", fileContent);

    // Close FIFOs
    close(fd1);
    close(fd2);

    return 0;
}
