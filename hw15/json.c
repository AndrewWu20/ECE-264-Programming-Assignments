#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <ctype.h>
#include <string.h>
#include "json.h"

static Node* _insert_a_tail(Node* a_head, Node* new_node);

static Node* _insert_a_tail(Node* a_head, Node* new_node) {			//Helper function to move thr position to the end of the list (a_tail)

	if(a_head == NULL) {
		a_head = new_node;
	}
	else {
		Node* pos_current = a_head;
		while(pos_current -> next != NULL) {
			pos_current = pos_current -> next;
		}
		pos_current -> next = new_node;
	}
	return a_head;
}

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

bool parse_string(char** a_string, char const** a_pos) {
	int index_of_string = 0;						//Variable for the index of string 
	int string_length = strlen(*a_pos);				//Variable for length of given string
	int counter = 0;								//Looping variable
	char const* a_position  = *a_pos;
	
	if((**a_pos != '"')) {							//If the first index isn't a ", return false
		return false;
	}
	*a_pos = *a_pos + 1;
	a_position++;
	while((counter < string_length) && (*a_position != '"')) {	//Loop through to check for null terminators and new line commands and to see how long the string is
		if((*a_position == '\n') || (*a_position == '\0')) {
			*a_pos += counter;
			return false;
		}
		a_position++;
		counter++;
	}
	if((counter == string_length) && (*a_position != '"')) {
		*a_pos += counter;
		return false;
	}
	*a_string = malloc(sizeof(**a_string) * (counter + 1));
	while(index_of_string < string_length && *(*a_pos + index_of_string) != '"') {		//Loop through string to copy values from a_pos to a_string
		(*a_string)[index_of_string] = (*a_pos)[index_of_string];
		index_of_string++;
	}
	(*a_string)[index_of_string] = '\0';										//Add null terminator
	*a_pos += index_of_string + 1;

	return true; 
}

bool parse_list(Node** a_head, char const** a_pos) {
	int comma_num = 0;
	int element_length = 0;

	if(**a_pos != '[') {											//Checks if the first element is a bracket, and returns false if not
		return false;
	}
	if((strlen(*a_pos) == 2) && ((**a_pos == '[') && (*(*a_pos + 1) == ']'))) {	//Accounts for empty lists
		return true;
	}
	*a_head = NULL;
	*a_pos = *a_pos + 1;
	char const* comma_address = *a_pos;
	while(**a_pos != '\0') {										//Loops through the list and adds elements to the list
		Element element_int_string_list;
		parse_element(&element_int_string_list, a_pos);
		if(**a_pos == ',') {
			comma_num++;
			*a_pos = *a_pos + 1;
		}
		Node* node = malloc(sizeof(*node));
		node -> element = element_int_string_list;
		*a_head = _insert_a_tail(*a_head, node);
		
		element_length++;
		//if(element_length == 2 && valid list) {
		//	return true;
		//}
		if(comma_num != 0) {										//Adjusts a_pos to the last element without commas
				(*a_pos) -= (*a_pos) - comma_address;
		}
		return true;
	}
	return false;
}

//Store the boolean output from parse element
//If it returns a meaningful thing, add to the list, return true
//if it doesn't, free the entire list and return false

bool parse_element(Element* a_element, char const** a_pos) {
	while (isspace(**a_pos)) {				//Loops through to eliminate whitespace
		*a_pos = *a_pos + 1;
	}

	if ((isdigit(**a_pos)) || (**a_pos == '-')) {	//Checks if the integer literal is an integer
		a_element -> type = ELEMENT_INT;
		return parse_int(&(a_element -> as_int), a_pos);
	}
	else if(**a_pos == '"') {						//Checks and prints if a_element is a string
		a_element -> type = ELEMENT_STRING;
		return parse_string(&(a_element -> as_string), a_pos);
	}
	else if(**a_pos == '[') {						//Checks and prints if a_element is a list
		a_element -> type = ELEMENT_LIST;
		return parse_list(&(a_element -> as_list), a_pos);
	}
	return false;
}

ParseResult parse_json(char const* json) {
	Element element;
	bool is_success = (parse_element(&element, &json)); //Getting the boolean of parse_element function

	ParseResult result_parsed = (ParseResult) { .is_success = is_success, .element = element }; 		//Initialization for a struct type with a compound literal

	return result_parsed;
}

void print_element(Element element) {
	if (element.type == ELEMENT_INT) {				//If integer literal is an integer type
		printf("%d", element.as_int);
	}
	if (element.type == ELEMENT_STRING) {			//If element is a string type
		printf("\"%s\"", element.as_string);
	}
//	if (element.type == ELEMENT_LIST) {
//		printf("[");
//		while(a_head != NULL) {
//			printf(
//		}
//		printf("]");
}

//Loop through the list with a for loop
//For every node you pass the element through print element, recursion

void free_element(Element element) {
	if(element.type == ELEMENT_STRING) {									//Frees strings
		free(element.as_string);
	}
	if(element.type == ELEMENT_LIST) {										//Frees a linked list
		while(element.as_list != NULL) {
			Node* temp_list = (element.as_list) -> next;
			free(element.as_list);
			element.as_list = temp_list;
		}
	}
}


/* vim: set tabstop=4 shiftwidth=4 fileencoding=utf-8 noexpandtab: */

