//
// Created by Henok Jackson on 08/10/26.
//
#ifndef FIBCALC_FIB_H
#define FIBCALC_FIB_H
#include <stdint.h>
#define MAX_DIGITS 99999999
#define NO_OF_ARRAYS 3

typedef struct {
    uint8_t num[MAX_DIGITS];
    unsigned long long int size;
} fibonacci_number;

fibonacci_number* allocate_fibonacci_buffer();

#endif //FIBCALC_FIB_H
