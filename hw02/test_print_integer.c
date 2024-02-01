#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include "print_integer.h"

int main(int argc, char* argv[]) 
{
	print_integer(0, 10, "");
	fputc('\n', stdout);

	print_integer(10, 10, "");
	fputc('\n', stdout);

	print_integer(100, 16, "");
	fputc('\n', stdout);

	print_integer(123, 10, "");
	print_integer(456, 10, "+");
	fputc('\n', stdout);

	print_integer(-728192, 10, "");
	fputc('\n', stdout);

	print_integer(100, 10, "$");
	fputc('\n', stdout);

	print_integer(30, 2, "");
	fputc('\n', stdout);

	print_integer(30, 36, "");
	fputc('\n', stdout);

	print_integer(50, 10, "bar");
	fputc('\n', stdout);

	print_integer(15, 11, "");
	fputc('\n', stdout);

	return EXIT_SUCCESS;
}
