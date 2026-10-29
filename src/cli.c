//
// Created by Henok Jackson on 08/10/26.
//
#include <ctype.h>
#include <limits.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../include/cli.h"
#include "../include/fibonacci.h"
#define DEFAULT_RANGE 1000

const char* const arg_range_str = "--range=\0";

static void show_cli_help() {
	printf("\n\nUsage: ./Fibonacci [RANGE ...]\n");
	printf("Examples:\n");
	printf("\tSpecifying range:\n");
	printf("\t\t--range=max\tGenerates the maximum possible fibonacci number that can be generated with the given heap.\n");
	printf("\t\t--range=N\tGenerates the Nth fibonacci number if enough heap space is available.\n");
}

static unsigned long long int parse_range(const char* args) {
	int index = 0;
	unsigned long long int range = 0;

	// case: maximum range
	if(strcmp(args, "--range=max") == 0) {
		/* TODO: Write the logic for setting range so that the loop runs infinitely.
		 * Currently using the max limit since it's impossible to estimate the highest
		 * fibonacci number with 'n' digits.
		 */
		return ULLONG_MAX;
	}

	// case: wrong argument
	for(; arg_range_str[index] != '\0'; index++) {
		if(args[index] != arg_range_str[index]) {
			printf("\nUnknown argument: %s", args);
			show_cli_help();
			return 0;
		}
	}

	// case: range argument specified, range parameter not specified
	if(args[index] == '\0') {
		printf("\nValue not specified for argument: %s", args);
		show_cli_help();
		return 0;
	}

	for(; args[index] != '\0'; index++) {
		// case: malformed range parameter
		if(!isdigit((unsigned char)args[index])) {
			printf("\nInvalid range: %s", args);
			show_cli_help();
			return 0;
		} else {
			range *= 10;
			range += args[index] - '0'; // character to integer conversion
		}
	}

	return range;
}

cli_params validate_cli_args(const int argc, char* args[]) {
	unsigned long long int range = 0;
	if (argc == 1) {
		range = DEFAULT_RANGE;
	} else if(argc == 2){
		range = parse_range(args[1]);
	} else {
		printf("\nInvalid number of arguments !");
		show_cli_help();
		exit(EXIT_FAILURE);
	}

	cli_params result;
	result.decision = (range == 0 ? false : true);
	result.range = range;

	return result;
}

void print_fib_num(const fibonacci_number* const ptr_fibonacci_number, const unsigned long long int ord) {
	if(ptr_fibonacci_number == nullptr) {
		printf("\nNull pointer exception !");
		exit(EXIT_FAILURE);
	}
	printf("Fibonacci Number (%llu) = \n\n", ord + 1);
	for(unsigned long long int i = (MAX_DIGITS - ptr_fibonacci_number -> size); i < MAX_DIGITS; i++) {
		printf("%d", ptr_fibonacci_number -> num[i]);
	}
}
