#ifndef RSA_PARAMS_H
#define RSA_PARAMS_H

#include <stdint.h>

// Declare the arrays as extern to allow for their use across different source files
extern uint64_t z[20];
extern uint64_t m[20];
extern uint64_t e[20];
extern uint64_t d[20];
extern uint64_t data[20];

#endif // RSA_PARAMS_H
