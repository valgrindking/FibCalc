// Copyright 2026. Henok Jackson
#include <ctype.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "../include/cli.h"
#include "../include/fibonacci.h"
#include "../include/performance_monitor.h"

int main(int argc, char* argv[]) {
	// validate command-line arguments
	const cli_params result = validate_cli_args(argc, argv);
	if(!result.decision) {
		exit(EXIT_FAILURE);
	}
	/*
	 * TODO: Ensure platform interoperability. This would work for POSIX systems
	 * but not on Non-POSIX systems. ensure it does not break on windows. If this is meant
	 * to be a math engine only then remove cli options. or maybe set build options to build the cli tool
	 * or the webserver
	 */
	system("clear");
	
	/*
	 * TODO: Write code such that the elements of the error will be set to zero prior to their setting of values.
	 */

	fibonacci_number* fibonacci[NO_OF_ARRAYS];
	for(int i = 0; i < NO_OF_ARRAYS; i++) {
		fibonacci[i] = allocate_fibonacci_buffer();
	}

	// initializing arrays
	memset(fibonacci[0] -> num, 0, sizeof(fibonacci[0] -> num));
	memset(fibonacci[1] -> num, 0, sizeof(fibonacci[1] -> num));
	memset(fibonacci[2] -> num, 0, sizeof(fibonacci[2] -> num));

	// mathematical parameters
	uint8_t carry = 0;
	unsigned long long int ord = 0;
	const unsigned long long int range = result.range;

	// set initial run flag
	bool is_initial_run = true;

	// initialize buffer pointers
	fibonacci_number *fibonacci_1_ptr = nullptr;
	fibonacci_number *fibonacci_2_ptr = nullptr;
	fibonacci_number *fibonacci_sum_ptr = nullptr;

	// start performance test
	perf_metric metric;
	start_perf_test(&metric);

	// calculate the Fibonacci series
	for(unsigned long long int j = 0; j < range - 1; j++) {
		// buffer pointer swap
		fibonacci_1_ptr = fibonacci[(j + 0) % NO_OF_ARRAYS];
		fibonacci_2_ptr = fibonacci[(j + 1) % NO_OF_ARRAYS];
		fibonacci_sum_ptr = fibonacci[(j + 2) % NO_OF_ARRAYS];
		fibonacci_sum_ptr -> size = fibonacci_2_ptr -> size;
		
		if(is_initial_run) {
			// initialize buffer params
			fibonacci_1_ptr -> size = 1;
			fibonacci_1_ptr -> num[MAX_DIGITS - 1] = 0;
			fibonacci_2_ptr -> size = 1;
			fibonacci_2_ptr -> num[MAX_DIGITS - 1] = 1;
			fibonacci_sum_ptr -> size = 1;

			// signal initial run done
			is_initial_run = false;
		}

		for(unsigned long long int i = MAX_DIGITS - 1; i > MAX_DIGITS - fibonacci_sum_ptr -> size - 1; i--) {
			uint8_t const sum = fibonacci_1_ptr -> num[i] + fibonacci_2_ptr -> num[i] + carry;
			carry = 0;

			// case: carry generated
			if (sum > 9) {
				carry = 1;
				if(MAX_DIGITS - fibonacci_2_ptr -> size == i) {
					fibonacci_sum_ptr -> size++;
				}
				fibonacci_sum_ptr -> num[i] = sum % 10;
			} else {
				fibonacci_sum_ptr -> num[i] = sum;
			}
			ord = j + 1;

			// buffer overflow detection
			if (fibonacci_sum_ptr -> num[0] != 0) {
				printf("Possible overflow in next iteration.\nTerminating....\n\n");
				print_fib_num(fibonacci_sum_ptr, ord);
				stop_perf_test(&metric);
				printf("\n\n\nCalculation Time: %Lf s\n\n", measure_exec_time(&metric));
				exit(EXIT_SUCCESS);
			}
		}
	}
	
	// stop performance test
	stop_perf_test(&metric);

	// print the fibonacci number
	print_fib_num(fibonacci_sum_ptr, ord);

	// log performance results
	printf("\n\nCalculation Time: %Lf s\n\n", measure_exec_time(&metric));

	return 0;
}
