// © 2020 Alexander J. Quinn.  All Rights Reserved.

#ifndef __PRINT_BITS_H__
#define __PRINT_BITS_H__

#include <stdint.h>

void print_bits_plain(uint8_t bits);
// Print the eight bits in 'bits' as plain text.  This does not print a newline at the end.
//
// Example:
// ∙ print_bits_plain(0xff) will output the same as
//   → printf("11111111").


void print_bits_color(uint8_t bits, uint8_t num_in_left, const char* color_l, const char* color_r);
// Print the eight bits in 'bits' with two sections in different colors.
//
// Example:
// ∙ print_bits_color(0x05, 3, "yellow", "red") will output the same as
//   → printf("%s000%s%s00101%s", "\x1b[33m", "\x1b[0m", "\x1b[31m", "\x1b[0m").
//
// ∙ print_bits_color(0x05, 3, "yellow", NULL) will output the same as
//   → printf("%s000%s00101", "\x1b[33m", "\x1b[0m", NULL, NULL).
//
// ∙ print_bits_color(0x05, 3, NULL, "red") will output the same as
//   → printf("000%s00101%s", NULL, NULL, "\x1b[31m", "\x1b[0m").
//

#endif /* end of include guard: __PRINT_BITS_H__ */
#define __PRINT_BITS_H_20200509T155212__
