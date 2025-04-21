#include <stdio.h>

int h[12];

void generateHammingCode();
void introduceError();
void correctError();

int main() {
    int i, choice;

    // Input message bits
    printf("\nEnter the 7-bit message: ");
    for (i = 1; i < 12; i++)
        if (i == 3 || i == 5 || i == 6 || i == 7 || i == 9 || i == 10 || i == 11)
            scanf("%d", &h[i]);

    generateHammingCode();

    printf("\nDo you want to introduce an error? (1 for Yes, 0 for No): ");
    scanf("%d", &choice);

    if (choice)
        introduceError();

    correctError();
    
    return 0;
}

// Generate Hamming code by calculating parity bits
void generateHammingCode() {
    int i;

    h[1] = (h[3] + h[5] + h[7] + h[9] + h[11]) % 2;
    h[2] = (h[3] + h[6] + h[7] + h[10] + h[11]) % 2;
    h[4] = (h[5] + h[6] + h[7]) % 2;
    h[8] = (h[9] + h[10] + h[11]) % 2;

    printf("\nTransmitted Hamming Code: ");
    for (i = 1; i < 12; i++)
        printf("%d ", h[i]);
    printf("\n");
}

// Introduce an error at a random position
void introduceError() {
    int pos;
    printf("\nEnter the bit position (1-11) to introduce an error: ");
    scanf("%d", &pos);
    
    if (pos < 1 || pos > 11) {
        printf("\nInvalid position!\n");
        return;
    }

    h[pos] ^= 1; // Flip the bit
    printf("\nCorrupted Hamming Code: ");
    for (int i = 1; i < 12; i++)
        printf("%d ", h[i]);
    printf("\n");
}

// Correct errors using Hamming Code parity checks
void correctError() {
    int errorPos = 0;

    errorPos += (h[1] != (h[3] + h[5] + h[7] + h[9] + h[11]) % 2) * 1;
    errorPos += (h[2] != (h[3] + h[6] + h[7] + h[10] + h[11]) % 2) * 2;
    errorPos += (h[4] != (h[5] + h[6] + h[7]) % 2) * 4;
    errorPos += (h[8] != (h[9] + h[10] + h[11]) % 2) * 8;

    if (errorPos) {
        printf("\nError detected at position: %d", errorPos);
        h[errorPos] ^= 1;  // Correct the error by flipping the bit
        printf("\nCorrected Hamming Code: ");
        for (int i = 1; i < 12; i++)
            printf("%d ", h[i]);
    } else {
        printf("\nNo error detected.");
    }

    printf("\n");
}

