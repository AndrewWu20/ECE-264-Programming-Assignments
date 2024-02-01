#ifndef __JOIN_STRINGS_H__
#define __JOIN_STRINGS_H__

char* join_strings(char const* const* strings, size_t num_strings, char const* separator);
char* copy_string(char const* string);
char* wrap_string(char const* string, char left_delimiter, char right_delimiter);

#define JOIN_STRINGS_H_VERSION = 2
#endif /* end of include guard: __JOIN_STRINGS_H__ */
