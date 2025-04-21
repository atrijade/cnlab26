#include <stdio.h>

#define MIN(x, y) ((x) < (y) ? (x) : (y)) // Macro to find min value

int main() {
    int bucket_size, output_rate, num_seconds, packets, i;
    int current_load = 0, dropped = 0;

    printf("LEAKY BUCKET ALGORITHM\n");
    printf("Enter bucket size: ");
    scanf("%d", &bucket_size);
    printf("Enter output rate: ");
    scanf("%d", &output_rate);
    printf("Enter number of seconds to simulate: ");
    scanf("%d", &num_seconds);

    printf("\n(SECOND)  (PACKETS RECVD)  (PACKETS SENT)  (PACKETS LEFT)  (PACKETS DROPPED)\n");

    for (i = 1; i <= num_seconds; i++) {
        printf("Enter number of packets at second %d: ", i);
        scanf("%d", &packets);

        // Add packets to the bucket
        current_load += packets;

        // If overflow occurs, drop excess packets
        if (current_load > bucket_size) {
            dropped = current_load - bucket_size;
            current_load = bucket_size;
        } else {
            dropped = 0;
        }

        // Send packets according to output rate
        int sent = MIN(current_load, output_rate);
        current_load -= sent;

        // Display bucket status
        printf("(%d)         (%d)               (%d)              (%d)              (%d)\n", i, packets, sent, current_load, dropped);
    }

    // Process remaining packets in the bucket
    while (current_load > 0) {
        int sent = MIN(current_load, output_rate);
        current_load -= sent;
        i++;
        printf("(%d)         (0)               (%d)              (%d)              (0)\n", i, sent, current_load);
    }

    return 0;
}
