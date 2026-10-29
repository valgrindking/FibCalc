//
// Created by Henok Jackson on 08/10/26.
//
#ifndef FIBCALC_CLI_H
#define FIBCALC_CLI_H

#include "../include/fibonacci.h"

typedef struct {
	bool decision;
	unsigned long long int range;
} cli_params;

extern const char* const arg_range_str;

cli_params validate_cli_args(int, char*[]);

void print_fib_num(const fibonacci_number*, unsigned long long int);

#endif

