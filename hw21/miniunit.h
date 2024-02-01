#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#ifndef _MINIUNIT_H_
#define _MINIUNIT_H_

#define MU_SUCCESS 0

#define mu_start()	int __mu_first_failure_line_number_or_0 = MU_SUCCESS    

#define mu_check(condition)															\
do {																				\
	if (((condition) == 0) && ((__mu_first_failure_line_number_or_0) == 0)) {				\
		__mu_first_failure_line_number_or_0 = __LINE__;							\
	}																				\
} while (false)																		\

#define mu_run(function)															\
do {																				\
	int failure_or_success = function();														\
	if (failure_or_success == 0) {					\
		printf("\x1b[32mTest passed:\x1b[0m %s\n", #function);							\
	} else {																		\
		printf("\x1b[31mTest failed:\x1b[0m %s \x1b[31mat line\x1b[0m %d\n", #function, failure_or_success);		\
	}																				\
} while (false)																		\

#define mu_end() 	return __mu_first_failure_line_number_or_0

#define mu_check_strings_equal(s1, s2)	mu_check(strcmp(s1, s2) == 0)

#endif  /* end of include guard: __MINIUNIT_H__ */
