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

static int _test_parse_element_invalid() {
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

int main(int argc, char* argv[]) {
	mu_run(_test_parse_element_int_plain);
	mu_run(_test_negative_integer);
	mu_run(_test_parse_element_with_whitespace);
	mu_run(_test_parse_element_oddballs);
	mu_run(_test_parse_element_invalid);
	
	return EXIT_SUCCESS;
}
/* vim: set tabstop=4 shiftwidth=4 fileencoding=utf-8 noexpandtab: */
