#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include "mintf.h"

static void _strings(char*);
static void _currency(int);

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
		n_mod = n_mod + -10 + 'a';
	}
	fputc(n_mod, stdout);							//Prints the modified number/character
}

void mintf(const char *format, ...) {
	va_list args;
	va_start(args, format);
	for(; *format != '\0'; format++) {
		if(*format == '%') {
			format++;	
			if(*format == 's') {
				char* str = va_arg(args, char*);
				_strings(str);
			} else if(*format == '%') {
				fputc(*format, stdout);
			} else if(*format == 'd') {
				int num = va_arg(args, int);
				print_integer(num, 10, "");
			} else if(*format == 'b') {
				int num = va_arg(args, int);
				print_integer(num, 2, "0b");
			} else if(*format == 'x') {
				int num = va_arg(args, int);
				print_integer(num, 16, "0x");
			} else if(*format == 'c') {
				char chr = (char) va_arg(args, int);
				fputc(chr, stdout);
			} else if(*format == '$') {
				int num = va_arg(args, int);
				_currency(num);
			} else {
				format--;
				fputc(*format, stdout);
			}
		} else {
			fputc(*format, stdout);
		}
	}
	va_end(args);
}

static void _strings(char* str) {
	for(int i = 0; str[i] != '\0'; i++) {
		fputc(str[i], stdout);
	}
}

static void _currency(int num) {
	if(num < 0) {
		fputc('-', stdout);
		num = num * -1;
	}
	print_integer((num / 100), 10, "$");
	fputc('.', stdout);
	if(num % 100 < 10) {
		fputc('0', stdout);
	}
	print_integer((num % 100), 10, "");
}
