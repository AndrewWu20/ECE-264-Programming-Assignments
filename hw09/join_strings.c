#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "join_strings.h"
#include "miniunit.h"

//Write of size 1
//Conditional


char* copy_string(char const* string) {
	char* empty = malloc(sizeof(*empty)*(strlen(string) + 1));
	memcpy(empty, string, strlen(string));
	empty[strlen(string)] = '\0';  //null terminator
	return empty; 
}

char* wrap_string(char const* string, char left_delimiter, char right_delimiter) {
	char* empty = malloc(sizeof(*empty)*(strlen(string) + 3));

	empty[0] = left_delimiter;
	memcpy(&empty[1], string, strlen(string));
	empty[strlen(string) + 1] = right_delimiter;
	
	empty[strlen(string) + 2] = '\0';  //Adding null terminator

	return empty;
}

char* join_strings(char const* const* strings, size_t num_strings, char const* separator) {
	if (num_strings == 0) {
		return copy_string("");
	}
	if (num_strings == 1) {
		return copy_string(strings[0]);
	}
	int memory_needed = 0;
	for (int i = 0; i < num_strings; i++) {
		memory_needed = memory_needed + strlen(strings[i]);
	}
	for (int i = 0; i < (num_strings - 1); i++) {
		memory_needed = memory_needed + strlen(separator);
	}
	memory_needed++;   //For null terminator

	char* empty = malloc(sizeof(*empty)*(memory_needed + 1));

	int memory_filled = 0;

	int i = 0;

	for (; i < (num_strings - 1); i++) {
		memcpy(&empty[memory_filled], strings[i], strlen(strings[i]));
		memory_filled = memory_filled + strlen(strings[i]);
		if (strlen(separator) != 0) {
			memcpy(&empty[memory_filled], separator, strlen(separator));
			memory_filled = memory_filled + strlen(separator);
		}
	}
	memcpy(&empty[memory_filled], strings[i], strlen(strings[i]));	
	memory_filled = memory_filled + strlen(strings[i]);
	empty[memory_filled] = '\0';	//Add null terminator
			
	return empty;
}
