#include <stdio.h>
#include <stdlib.h>
#include<stdarg.h>
#include "mintf.h"

int main(int argc, char* argv[]) {

	mintf("");
	fputc('\n', stdout);

	mintf("98275927\n");
	fputc('\n', stdout);

	mintf("The percentage is 20%%");
	fputc('\n', stdout);

	mintf("The first letter of apple is %c", 'a');
	fputc('\n', stdout);

	mintf("%s", "Purdue is in Indiana");
	fputc('\n', stdout);

	mintf("%b", 125);
	fputc('\n', stdout);

	mintf("%x", 985);
	fputc('\n', stdout);

	mintf("Tommy has %d dogs.", 3);
	fputc('\n', stdout);

	mintf("There are %d red, %d green, and %d blue balls in the bag.", 20, 50, 30);
	fputc('\n', stdout);

	mintf("After buying a %$ phone, Ryan has %$ and is currently in debt.", 1001, -111);
	fputc('\n', stdout);

	mintf("The number %d is %b in binary.", 47, 47);
	fputc('\n', stdout);

	mintf("Invalid test: %a");
	fputc('\n', stdout);

	return EXIT_SUCCESS;
}

