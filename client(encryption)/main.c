#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include "./rsa-related/rsa_params.h"  
#include "./rsa-related/rsa.h"  
#include "socket_communication.h"

///Running the code
// gcc -std=c11 -o send_encrypted_data  main.c socket_communication.c ./rsa-related/rsa_params.c ./rsa-related/rsa.c -lm
// ./send_encrypted_data

void print_array(const char *label, const uint64_t arr[], size_t size) {
    printf("%s:\n", label);
    for (size_t i = 0; i < size; i++) {
        printf("%016llx ", arr[i]);
        if ((i + 1) % 4 == 0)  
            printf("\n");
    }
    printf("\n");
}

int main(int argc, char *argv[]) {
    print_array("Modulus", m, 20);
    print_array("Server public key", e, 20);
    print_array("Initial Data", data, 20);

    printf("Performing RSA encryption...\n");
    if (!rsa1024(z, data, e, m)) {
        printf("RSA encryption failed.\n");
        return 1;  
    }
    print_array("Output after RSA encryption", z, 20);
   
    send_encrypted_data(z);

    return 0;
}