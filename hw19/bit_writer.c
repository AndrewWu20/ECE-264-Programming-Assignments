#include <assert.h>
#include "bit_writer.h"

BitWriter open_bit_writer(const char* path) {
	return(BitWriter) { .file = fopen(path, "w"), .current_byte = 0, .num_bits_left = 8};		//Declarations of variables in a compound literal 
}

void write_bits(BitWriter* a_writer, uint8_t bits, uint8_t num_bits_to_write) {
	assert(num_bits_to_write >= 0 && num_bits_to_write <= 8);
	assert(a_writer->num_bits_left >= 1 && a_writer->num_bits_left <= 8);

	if(num_bits_to_write <= a_writer -> num_bits_left) {										//If the number of bits left can fit in the byte, write the remaining bits to the same byte
		uint8_t write_bits = (bits << ((a_writer -> num_bits_left) - num_bits_to_write)) & (0xFF >> (8 - (a_writer -> num_bits_left)));
		(a_writer -> current_byte) |= write_bits;
		(a_writer -> num_bits_left) -= num_bits_to_write;
	}
	else {																						//Else (aka straddling), straddle the remaining bits into the next byte
		int old_number_bits_left = num_bits_to_write - (a_writer -> num_bits_left); // Store current number of bits open so we know how many to add later

		uint8_t write_bits = (bits >> old_number_bits_left) & (0xFF >> (8 - (a_writer -> num_bits_left))); // Move wanted bits then remove others
		
		(a_writer -> current_byte) |= write_bits;
		
		flush_bit_writer(a_writer);
		
		(a_writer -> current_byte) |= bits << (8 - old_number_bits_left);
		(a_writer -> num_bits_left) -= old_number_bits_left;
	}
	if(a_writer -> num_bits_left == 0) {
		flush_bit_writer(a_writer);
	}

	assert(a_writer->num_bits_left >= 1 && a_writer->num_bits_left <= 8);
}

void flush_bit_writer(BitWriter* a_writer) {
	if (a_writer -> num_bits_left != 8) {														//Writes the bits into the byte
		fputc(a_writer -> current_byte, (a_writer -> file));
		a_writer -> current_byte = 0;
		a_writer -> num_bits_left = 8;
	}
}

void close_bit_writer(BitWriter* a_writer) {													//Closing the bit writer function
	flush_bit_writer(a_writer);
	fclose(a_writer -> file);
	a_writer -> file = NULL;
}

#define __BIT_WRITER_C_V1__
/* vim: set tabstop=4 shiftwidth=4 fileencoding=utf-8 noexpandtab colorcolumn=96: */
