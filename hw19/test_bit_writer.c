#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include "miniunit.h"
#include "bit_writer.h"

static int _test_write_bits_easy() {								//Tests writing a simple bit into a byte
	mu_start();
	//
	BitWriter write = open_bit_writer("easy.bits");
	write_bits(&write, 0x03, 4);
	close_bit_writer(&write);

	FILE *file = fopen("easy.bits", "r");
	mu_check(fgetc(file) == 0x30);

	fclose(file);
	//
	mu_end();
}

static int _test_write_bits_harder() {								//Tests writing multiple bits into a byte
	mu_start();
	//
	BitWriter write = open_bit_writer("multiple.bits");
	write_bits(&write, 0x01, 2);
	write_bits(&write, 0x02, 2);
	write_bits(&write, 0x03, 2);
	write_bits(&write, 0x04, 2);
	close_bit_writer(&write);

	FILE *file = fopen("multiple.bits", "r");
	mu_check(fgetc(file) == 0x6C);

	fclose(file);
	//
	mu_end();
}

static int _test_write_bits_straddle_bytes() {						//Tests straddling bits into multiple bytes
	mu_start();
	//
	BitWriter write = open_bit_writer("straddle.bits");
	write_bits(&write, 0x0e, 3);
	write_bits(&write, 0x12, 3);
	write_bits(&write, 0x13, 4);
	close_bit_writer(&write);

	FILE *file = fopen("straddle.bits", "r");
	mu_check(fgetc(file) == 0xc8);
	mu_check(fgetc(file) == 0xc0);

	fclose(file);
	//
	mu_end();			
}

int main(int argc, char* argv[]) {
	mu_run(_test_write_bits_easy);
	mu_run(_test_write_bits_harder);
	mu_run(_test_write_bits_straddle_bytes);

	return EXIT_SUCCESS;
}
/* vim: set tabstop=4 shiftwidth=4 fileencoding=utf-8 noexpandtab: */
