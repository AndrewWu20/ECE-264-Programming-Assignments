#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "join_strings.h"
#include "miniunit.h"

static int _test_copy_string_empty() {
	mu_start();
	//--------------------
	char const* s_orig = "";
	char* s_copy = copy_string(s_orig);
	mu_check_strings_equal(s_copy, s_orig);
	free(s_copy);
	//--------------------
	mu_end();
}

static int _test_copy_string_abc() {
	mu_start();
	//--------------------
	char const* s_orig = "abc";
	char* s_copy = copy_string(s_orig);
	mu_check_strings_equal(s_copy, s_orig);
	free(s_copy);
	//--------------------
	mu_end();
}

static int _test_wrap_string_empty() {
	mu_start();
	//--------------------
	char* s_copy = wrap_string("", '[', ']');
	mu_check_strings_equal(s_copy, "[]");
	free(s_copy);
	//--------------------
	mu_end();
}

static int _test_wrap_string_abc() {
	mu_start();
	//--------------------
	char* s_copy = wrap_string("abc", '[', ']');
	mu_check_strings_equal(s_copy, "[abc]");
	free(s_copy);
	//--------------------
	mu_end();
}

static int _test_join_strings_one() {
	mu_start();
	//--------------------
	char const* const strings[] = { "abc" };
	char* combined_str = join_strings(strings, 1, "-");
	mu_check_strings_equal(combined_str, "abc");
	free(combined_str);
	//--------------------
	mu_end();
}

static int _test_join_strings_three_empty_delimiter() {
	mu_start();
	//--------------------
	char const* const strings[] = { "abc", "def", "ghi" };
	char* combined_str = join_strings(strings, 3, "");
	mu_check_strings_equal(combined_str, "abcdefghi");
	free(combined_str);
	//--------------------
	mu_end();
}

static int _test_join_strings_three_nonempty_delimiter() {
	mu_start();
	//--------------------
	char const* const strings[] = { "abc", "def", "ghi" };
	char* combined_str = join_strings(strings, 3, "-");
	mu_check_strings_equal(combined_str, "abc-def-ghi");
	free(combined_str);
	//--------------------
	mu_end();
}

static int _test_join_strings_num_strings_0() {
	mu_start();

	char* combined_str = join_strings(NULL, 0, "");
	mu_check_strings_equal(combined_str, "");
	free(combined_str);
	
	mu_end();
}

static int _test_join_strings_num_strings_1() {
	mu_start();

	char const* const strings[] = { "abcde" };
	char* combined_str = join_strings(strings, 1, "");
	mu_check_strings_equal(combined_str, "abcde" );
	free(combined_str);

	mu_end();
}

int main(int argc, char* argv[]) {
	
	mu_run(_test_copy_string_empty);
	mu_run(_test_copy_string_abc);
	mu_run(_test_wrap_string_empty);
	mu_run(_test_wrap_string_abc);
	mu_run(_test_join_strings_one);
	mu_run(_test_join_strings_three_empty_delimiter);
	mu_run(_test_join_strings_three_nonempty_delimiter);
	mu_run(_test_join_strings_num_strings_0);
	mu_run(_test_join_strings_num_strings_1);
	return EXIT_SUCCESS;
}
