// rsa_decryption.h
#ifndef RSA_DECRYPTION_H
#define RSA_DECRYPTION_H

#include <stdint.h>
#include <stdbool.h>

// Function to decrypt data
bool decrypt_rsa(uint64_t z[20]);

#endif // RSA_DECRYPTION_H