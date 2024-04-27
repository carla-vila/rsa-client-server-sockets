#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h> 
#include "./rsa-related/rsa_params.h"
#include "./rsa-related/rsa.h"
#include "decryption.h"

#define PORT 12345

// gcc -std=c11 -o server_program server_program.c decryption.c ./rsa-related/rsa_params.c ./rsa-related/rsa.c -lm

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    char buffer[1024] = {0};

    // Creating socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // Forcefully attaching socket to the port
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt))) {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY; // Bind to all available network interfaces
    address.sin_port = htons(PORT);

    // Binding socket to the port
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address))<0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 3) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen))<0) {
        perror("accept");
        exit(EXIT_FAILURE);
    }
    
    int valread;
    while(1) {
        memset(buffer, 0, sizeof(buffer));
        if ((valread = read(new_socket, buffer, sizeof(buffer) - 1)) > 0) {
            printf("Received encrypted data in decimal: %s\n", buffer);
            uint64_t z[20] = {0}; // Assuming the expected number of integers is known
            char *ptr = buffer;
            int idx = 0;
            while (*ptr && idx < 20) {
                z[idx++] = strtoull(ptr, &ptr, 10);
                while (*ptr == ' ') ptr++; // Skip spaces
            }

            if (decrypt_rsa(z)) {
                printf("Decryption successful.\n");
            } else {
                printf("Decryption failed.\n");
            }
        }
        if (valread == 0) {
            printf("Connection closed by client.\n");
            break;
        }
    }
    return 0;
}
