#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "log_macros.h"

int main(int argc, char* argv[]) {

	printf("\nTest 1\n");
	printf("3 + 4 == %d\n", 3 + 4);
	log_int(3 + 4);

	printf("\nTest 2\n");
	int population = 51605;
	printf("population == %d\n", population);
	log_int(population);

	printf("\nTest 3\n");
	printf("'A' == '%c'\n", 'A');
	log_char('A');

	printf("\nTest 4\n");
	printf("65 == '%c'\n", 65);
	log_char(65);

	printf("\nTest 5\n");
	char* city_name = "West Lafayette";
	printf("city_name[0] == '%c'\n", city_name[0]);
	log_char(city_name[0]);

	printf("\nTest 6\n");
	printf("city_name == \"%s\"\n", city_name);
	log_str(city_name);

	printf("\nTest 7\n");
	printf("city_name == %p\n", (void*)city_name);
	log_addr(city_name);

	printf("\nTest 8\n");
	printf("NULL == (nil)\n");
	log_addr(NULL);

	printf("\nTest 9\n");
	printf("1.0 / 65536 == %.016f\n", 1.0 / 65536);
	log_float(1.0 / 65536);

	printf("\nTest 10\n");
	printf("1.234567890123456e-1 == %.016f\n", 1.234567890123456e-1);
	log_float(1.234567890123456e-1);
	// 1.234567890123456e-1 is scientific notation for 1.234567890123456 x 10⁻¹ (0.1234567890123456)

	printf("\nTest 11\n");
	printf("0x1p-16 == %.016f\n", 0x1p-16);
	log_float(0x1p-16);
	// 0x1p-16 is BINARY scentification notation for 1.0 x 2⁻¹⁶ == 0.0000152587890625.

	printf("\nTest 12\n");
	printf("false == false\n");
	log_bool(false);

	printf("\nTest 13\n");
	printf("true == true\n");
	log_bool(true);

	printf("\nTest 14\n");
	printf("3 > 5 == false\n");
	log_bool(3 > 5);

	printf("\nTest 15\n");
	printf("3 > 1 == true\n");
	log_bool(3 > 1);

	return EXIT_SUCCESS;
}
/* vim: set tabstop=4 shiftwidth=4 fileencoding=utf-8 noexpandtab: */
