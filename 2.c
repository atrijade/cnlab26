#include <stdio.h>
#include <string.h>

#define POLY "10011"  // Degree-4 CRC Polynomial (x^4 + x + 1)
#define CRC_LEN 4

void computeCRC(char data[], char crc[]) {
    char temp[120];  
    strcpy(temp, data);
    strcat(temp, "0000");  // Append 4 zeros for degree-4 polynomial

    for (int i = 0; i < strlen(data); i++) {
        if (temp[i] == '1') {
            for (int j = 0; j < CRC_LEN + 1; j++)
                temp[i + j] = (temp[i + j] == POLY[j]) ? '0' : '1';
        }
    }
    strncpy(crc, temp + strlen(data), CRC_LEN);
    crc[CRC_LEN] = '\0';
}

int checkCRC(char frame[]) {
    char receivedCRC[CRC_LEN + 1];
    computeCRC(frame, receivedCRC);
    return strcmp(receivedCRC, "0000") == 0;  // All zeros means no error
}

int main() {
    char data[100], crc[CRC_LEN + 1], frame[120];

    printf("Enter binary data: ");
    scanf("%s", data);

    computeCRC(data, crc);
    strcpy(frame, data);
    strcat(frame, crc);

    printf("\nTransmitted Frame: %s\n", frame);

    printf("\nEnter received frame: ");
    scanf("%s", frame);

    if (checkCRC(frame))
        printf("Frame is ERROR-FREE\n");
    else
        printf("Frame has ERRORS!\n");

    return 0;
}
