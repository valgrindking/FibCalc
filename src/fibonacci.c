//
// Created by Henok Jackson on 08/10/26.
//

/*
 * TODO: Write code to allocate memory for the fibonacci arrays
 */
#include <stdio.h>
#include <stdlib.h>
#include "fibonacci.h"

fibonacci_number* allocate_fibonacci_buffer() {
    fibonacci_number* ptr_fibonacci_number = malloc(sizeof(fibonacci_number));
    return ptr_fibonacci_number;
}

