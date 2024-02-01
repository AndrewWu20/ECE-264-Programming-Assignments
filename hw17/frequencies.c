#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <errno.h>
#include <string.h>
#include "frequencies.h"

bool calc_frequencies(Frequencies freqs, const char* path, const char** a_error) {
	FILE* opened_file = fopen(path, "r");				//Create file variable

	if(opened_file == NULL) {							//Returns false if the file does not exist
		*a_error = strerror(errno);
		return false;
	}
	for(char character = fgetc(opened_file); !feof(opened_file); character = fgetc(opened_file)) {		//Increments when character appears in the file
		freqs[character + 0] += 1;
	}
	fclose(opened_file);
	return true;
}

/* vim: set tabstop=4 shiftwidth=4 fileencoding=utf-8 noexpandtab: */
