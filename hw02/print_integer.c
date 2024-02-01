#include <stdio.h>
#include "print_integer.h"

void print_integer(int n, int radix, char* prefix) {
	unsigned int abs_val_n = n;						//Type can deal with larger values
	if(n < 0) {										//If statement prints a negative sign out front if the input number is negative
		fputc('-', stdout);
		abs_val_n = n * -1;
	}
	for(int i = 0; prefix[i] != '\0'; i++) {		//For loop deals with prefix inputs
		fputc(prefix[i], stdout);
	}
	int n_mod = (abs_val_n % radix);				//Converts input number into specified base
	abs_val_n = abs_val_n / radix;
	if(abs_val_n > 0) {								//Calls the function recurssively if the remainder is greater than zero
		print_integer(abs_val_n, radix, "");
	}
	if(n_mod < 10) {								//Assigns the number if the modded number is less than ten
		n_mod = n_mod + '0';
	}
	else {											//Assigns the lowercase character associated with the modded number if it is not less than ten
		n_mod = n_mod + 'W';
	}
	fputc(n_mod, stdout);							//Prints the modified number/character
}
