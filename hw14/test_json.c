#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include "json.h"
#include "miniunit.h"

static int _test_parse_element_int_plain() {			//Tests a simple input of one integer
	mu_start();
	//
	Element element;
	char const* input = "1";
	char const* pos = input;
	bool is_success = parse_element(&element, &pos);
	mu_check(is_success);
	mu_check(element.as_int == 1);
	mu_check(element.type == ELEMENT_INT);
	mu_check(pos == input + 1);
	mu_check(*pos == '\0');
	//
	mu_end();
}

static int _test_negative_integer() {					//Tests a negative integer input
	mu_start();
	//
	Element element;
	char const* input = "-2";
	char const* pos = input;
	bool is_success = parse_element(&element, &pos);
	mu_check(is_success);
	mu_check(element.as_int == -2);
	mu_check(element.type == ELEMENT_INT);
	mu_check(pos == input + 2);
	mu_check(*pos == '\0');
	//
	mu_end();
}

static int _test_parse_element_with_whitespace() {		//Tests an input with whitespace
	mu_start();
	//
	Element element;
	char const* input = " 1";
	char const* pos = input;
	bool is_success = parse_element(&element, &pos);
	mu_check(is_success);
	mu_check(element.as_int == 1);
	mu_check(element.type == ELEMENT_INT);
	mu_check(pos == input + 2);
	mu_check(*pos == '\0');
	//
	mu_end();
}

static int _test_parse_element_oddballs() {				//Tests an input with whitespaces in various positions
	mu_start();
	//
	Element element;
	char const* input = " 4 A";
	char const* pos = input;
	bool is_success = parse_element(&element, &pos);
	mu_check(is_success);
	mu_check(element.as_int == 4);
	mu_check(element.type == ELEMENT_INT);
	mu_check(pos == input + 2);
	mu_check(*pos == ' ');
	//
	mu_end();
}

static int _test_parse_element_invalid() {				//Tests an invalid string
	mu_start();
	//
	Element element;
	char const* input = "--4";
	char const* pos = input;
	bool is_success = parse_element(&element, &pos);
	mu_check(!is_success);
	mu_check(pos == input +1);
	mu_check(*pos == '-');
	//
	mu_end();
}

static int _test_parse_string_valid_empty() {			//Tests an empty string
	mu_start();
	//
	char* result;
	char const* input = "\"\"";
	char const* pos = input;
	bool is_success = parse_string(&result, &pos);
	mu_check(is_success);
	mu_check_strings_equal("", result);
	mu_check(pos == input + 2);
	mu_check(*pos == '\0');
	free(result);
	//
	mu_end();
}

static int _test_parse_string_valid_one_char() {		//Tests a string with one character
	mu_start();
	//
	char* result;
	char const* input = "\"A\"";
	char const* pos = input;
	bool is_success = parse_string(&result, &pos);
	mu_check(is_success);
	mu_check_strings_equal("A", result);
	mu_check(pos == input + 3);							
	mu_check(*pos == '\0');
	free(result);
	//
	mu_end();
}

static int _test_parse_string_valid_multiple_chars() {	//Tests a string with multiple characters
	mu_start();
	//
	char* result;
	char const* input = "\"ABC\"";
	char const* pos = input;
	bool is_success = parse_string(&result, &pos);
	mu_check(is_success);
	mu_check_strings_equal("ABC", result);
	mu_check(pos == input + 5);							
	mu_check(*pos == '\0');
	free(result);
	//
	mu_end();
}

static int _test_parse_string_invalid() {				//Tests an invalid string
	mu_start();
	//
	char* result;
	char const* input = "\"A";
	char const* pos = input;
	bool is_success = parse_string(&result, &pos);
	mu_check(! is_success);
	mu_check(pos == input + 2);							
	mu_check(*pos == '\0');


	input = "\"A\nB\"";
	pos = input;
	is_success = parse_string(&result, &pos);
	mu_check(! is_success);
	mu_check(pos == input + 2);
	mu_check(*pos == '\n');
	//
	mu_end();
}

static int _test_parse_element_string() {				//Tests a valid string
	mu_start();
	//
	Element element;
	char const* input = "\"ABC\"";
	char const* pos = input;
	bool is_success = parse_element(&element, & pos);
	mu_check(is_success);
	mu_check_strings_equal("ABC", element.as_string);
	mu_check(element.type == ELEMENT_STRING);
	mu_check(pos == input + 5);							
	mu_check(*pos == '\0');
	free_element(element);
	//
	mu_end();
}

static int _test_print_element_int() {					//Tests printing an integer
	Element element;
	char const* input = "123";
	bool is_success = parse_element(&element, &input);
	if(is_success == true) {
		printf("Success");
	}
	printf("Testing parse_element(&element, \"123\")\n");
	printf(" - Expected: 123\n");
	printf(" - Actual: ");
	print_element(element);
	fputc('\n', stdout);
	free_element(element);
	return(is_success);
}

static int _test_print_element_string() {				//Tests printing a string
	mu_start();
	//
	Element element;
	char const* input = "\"ABC\"";
	bool is_success = parse_element(&element, &input);
	mu_check(is_success);
	printf("Testing parse_element(&element, \"\\\"ABC\\\"\")\n");
	printf(" - Expected: \"ABC\"\n");
	printf(" - Actual: ");
	print_element(element);
	fputc('\n', stdout);
	free_element(element);
	//
	mu_end();
}

static int _test_parse_list_empty() {					//Tests an empty list
	mu_start();
	//
	char const* input = "[]";
	char const* pos = input;
	Node* empty = NULL;
	bool is_success = parse_list(&empty, &pos);
	mu_check(is_success);
	if(is_success != 0) {
		mu_check(empty -> next == NULL);
		mu_check(empty -> element.as_list == NULL);
	}
	free_element(empty -> element);
	//
	mu_end();
}

static int _test_parse_list_one_int() {					//Tests a list with an integer inside
	mu_start();
	//
	char const* input = "[5]";
	char const* pos = input;
	Node* integer = NULL;
	bool is_success = parse_list(&integer, &pos);
	mu_check(is_success);
	if(is_success != 0) {
		mu_check(integer -> element.as_list != NULL);
	}
	free_element(integer -> element);
	//
	mu_end();
}

//static voit _test_print_list() {						//Tests printing a list
//	Element element;
//	char const* input = "012";
//	bool is_success = parse_element(&element, &input);
//	printf("Testing parse_element(&element, \"012\")\n");
//	printf("Expected: 012\n");
//	printf("Actual: ");
//	print_element(element);
//	fputc('\n', stdout);
//	free_element(element);
//}

int main(int argc, char* argv[]) {
	mu_run(_test_parse_element_int_plain);
	mu_run(_test_negative_integer);
	mu_run(_test_parse_element_with_whitespace);
	mu_run(_test_parse_element_oddballs);
	mu_run(_test_parse_element_invalid);
	mu_run(_test_parse_string_valid_empty);
	mu_run(_test_parse_string_valid_one_char);
	mu_run(_test_parse_string_valid_multiple_chars);
	mu_run(_test_parse_string_invalid);
	mu_run(_test_parse_element_string);
	mu_run(_test_print_element_int);
	mu_run(_test_print_element_string);
	mu_run(_test_parse_list_empty);
	mu_run(_test_parse_list_one_int);
//	mu_run(_test_print_list);

	return EXIT_SUCCESS;
}
/* vim: set tabstop=4 shiftwidth=4 fileencoding=utf-8 noexpandtab: */
