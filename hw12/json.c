#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <ctype.h>
#include <string.h>
#include "json.h"

bool parse_int(int* a_value, char const** a_pos) {

	if ((**a_pos != '-') && (isdigit(**a_pos) == 0)) {		//Checks if the element is an invalid integer literal
		return false;
	}
	else {
		int negative_var = 0;
		if (**a_pos == '-') {						//Checks if the integer literal is a negative value
			*a_pos = *a_pos + 1;
			negative_var++;
		}
		if(isdigit(**a_pos) == 0) {
			return false;
		}
		*a_value = 0;
		while (isdigit(**a_pos)) {					//Loops through to update a_value
			int number = (**a_pos - '0');
			*a_value = *a_value * 10;
			*a_value = number + *a_value;
			*a_pos = *a_pos + 1;
		}
		if (negative_var == 1) {					//Checks and multiplies by -1 if the integer literal is negative
			*a_value = *a_value * -1;
		}
		return true;
	}
}

bool parse_element(Element* a_element, char const** a_pos) {
	while (isspace(**a_pos)) {				//Loops through to eliminate whitespace
		*a_pos = *a_pos + 1;
	}

	if ((isdigit(**a_pos)) || (**a_pos == '-')) {	//Checks if the integer literal is an integer
		a_element -> type = ELEMENT_INT;
		return parse_int(&(a_element -> as_int), a_pos);
	}
	else {
		return false;
	}
}

ParseResult parse_json(char const* json) {
	Element element;
	bool is_success = (parse_element(&element, &json)); //Getting the boolean of parse_element function

	ParseResult result_parsed = (ParseResult) { .is_success = is_success, .element = element }; 		//Initialization for a struct type with a compound literal

	return result_parsed;
}

void print_element(Element element) {
	if (element.type == ELEMENT_INT) {				//If integer literal is an integer type
		printf("\"element:\"\"%d\"", element.as_int);
	}
}

void free_element(Element element) {
	
}


/* vim: set tabstop=4 shiftwidth=4 fileencoding=utf-8 noexpandtab: */
