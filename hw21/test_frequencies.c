#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include "frequencies.h"
#include "miniunit.h"

//Needs 100% code coverage
//Must have one error case, ie opening a file that does not exist

static int _test_frequencies_invalid_file() {									//Tests a non-existent file
	mu_start();
	//
	char const* error;
	Frequencies freqs = {0};
	bool is_success = calc_frequencies(freqs, "null.txt", &error);
	mu_check(!is_success);
	//
	mu_end();
}

static int _test_frequencies_valid_file() {										//Tests a valid file with characters
	mu_start();
	//
	char const* error;
	Frequencies freqs = {0};
	bool is_success = calc_frequencies(freqs, "valid.txt", &error);
	mu_check(is_success);

	for(int i = 97; i <= 122; i ++) {
		mu_check(freqs[i] == 1);
	}
	//
	mu_end();
}

static int _test_frequencies_obscure_char() {									//Tests a valid file with obscure characters 
	mu_start();
	//
	char const* error;
	Frequencies freqs = {0};
	bool is_success = calc_frequencies(freqs, "obscure.txt", &error);
	mu_check(is_success);
	mu_check(freqs[126] == 3);
	mu_check(freqs[60] == 1);
	mu_check(freqs[58] == 1);
	mu_check(freqs[59] == 1);
	mu_check(freqs[10] == 4);
	//
	mu_end();
}

int main(int argc, char* argv[]) {
	mu_run(_test_frequencies_invalid_file);
	mu_run(_test_frequencies_valid_file);
	mu_run(_test_frequencies_obscure_char);

	return EXIT_SUCCESS;
}
/* vim: set tabstop=4 shiftwidth=4 fileencoding=utf-8 noexpandtab: */
