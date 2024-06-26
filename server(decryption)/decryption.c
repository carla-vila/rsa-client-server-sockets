#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include "./rsa-related/rsa.h"
#include "./rsa-related/rsa_params.h"

void print_array(const char *label, const uint64_t arr[], size_t size) {
    printf("%s:\n", label);
    for (size_t i = 0; i < size; i++) {
        printf("%016llx ", arr[i]);
        if ((i + 1) % 4 == 0)  
            printf("\n");
    }
    printf("\n");
}

bool decrypt_rsa(uint64_t z[20]) {
    print_array("Modulus in hexadecimal", m, 20);
    print_array("Server private key in hexadecimal", d, 20);
    print_array("Encrypted message received in hexadecimal", z, 20);
    
    uint64_t decrypted[20] = {0};
    printf("Performing RSA decryption...\n");
    if (!rsa1024(data, z, d, m)) {
        printf("RSA decryption failed.\n");
        return false;
    }
    print_array("Initial data, output after RSA decryption in hexadecimal", data, 20);
    return true;
}
