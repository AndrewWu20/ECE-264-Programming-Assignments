#include <stdio.h>									
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include "sorts.h"
#include "miniunit.h"

static int _test_one_input() {						//Tests one input
	mu_start();
	//
	int sort_array[] = {1};
	tree_sort_array(sort_array, 1);
	mu_check(sort_array[0] == 1);
	//
	mu_end();
}

static int _test_three_input() {					//Test three inputs
	mu_start();
	//
	int sort_array[] = {5, 3, 7};
	tree_sort_array(sort_array, 3);
	mu_check(sort_array[0] == 3);
	mu_check(sort_array[1] == 5);
	mu_check(sort_array[2] == 7);
	//
	mu_end();
}

static int _test_simple() {							//Test a simple array
	mu_start();
	//
	int sort_array[] = {3, 5, 6, 2, 4, 7, 1};
	tree_sort_array(sort_array, 7);
	mu_check(sort_array[0] == 1);
	mu_check(sort_array[3] == 4);
	mu_check(sort_array[6] == 7);
	//
	mu_end();
}

static int _test_double_jump() {					//Tests an array that has a difference of two between numbers
	mu_start();
	//
	int sort_array[] = {4, 6, 2, 10, 8, 14, 12};
	tree_sort_array(sort_array, 7);
	mu_check(sort_array[0] == 2);
	mu_check(sort_array[2] == 6);
	mu_check(sort_array[5] == 12);
	//
	mu_end();
}

static int _test_random() {							//Tests an array that has no pattern between its numbers
	mu_start();
	//
	int sort_array[] = {1, 7, 3, 9, 13, 21, 16, 10};
	tree_sort_array(sort_array, 8);
	mu_check(sort_array[2] == 7);
	mu_check(sort_array[0] == 1);
	mu_check(sort_array[7] == 21);
	//
	mu_end();
}

int main(int argc, char* argv[]) {					//Main function to run all of the test functions
	mu_run(_test_one_input);
	mu_run(_test_three_input);
	mu_run(_test_simple);
	mu_run(_test_double_jump);
	mu_run(_test_random);

	return EXIT_SUCCESS;
}
/* vim: set tabstop=4 shiftwidth=4 fileencoding=utf-8 noexpandtab: */
