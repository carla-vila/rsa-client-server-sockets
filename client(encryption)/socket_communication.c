#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT 12345
#define SERVER_IP "192.168.1.36"

void send_encrypted_data(uint64_t z[20]) {
    int sock = 0;
    struct sockaddr_in serv_addr;
    char message[2048] = {0}; // Increase buffer size to accommodate all numbers

    // Create a large string of all numbers in the array
    char *ptr = message;
    int remaining_size = sizeof(message);
    for (int i = 0; i < 20; i++) {
        int written = snprintf(ptr, remaining_size, "%llu ", z[i]); // Use %llu for uint64_t and add space
        if (written > 0 && written < remaining_size) {
            ptr += written;
            remaining_size -= written;
        } else {
            fprintf(stderr, "Buffer overflow when preparing message\n");
            exit(EXIT_FAILURE);
        }
    }

    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
    serv_addr.sin_addr.s_addr = inet_addr(SERVER_IP);

    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        perror("connection failed");
        exit(EXIT_FAILURE);
    }

    // Send the encrypted data to the server
    if (send(sock, message, strlen(message), 0) < 0) {
        perror("send failed");
        exit(EXIT_FAILURE);
    }
    printf("Encrypted data sent: %s\n", message);

    close(sock);
}