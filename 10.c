#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <arpa/inet.h>

int main() {
    char hostname[100];
    struct hostent *host;
    struct in_addr **addr_list;

    // Get domain name from user
    printf("Enter domain name: ");
    scanf("%s", hostname);

    // Get host details
    host = gethostbyname(hostname);
    if (host == NULL) {
        printf("DNS resolution failed! Domain not found.\n");
        return 1;
    }
    printf("Hello before the address");
    // Print IP addresses
    printf("IP Address(es) for %s:\n", hostname);
    addr_list = (struct in_addr **)host->h_addr_list;
    
    for (int i = 0; addr_list[i] != NULL; i++) {
        printf(" - %s\n", inet_ntoa(*addr_list[i]));
    }

    return 0;
}
