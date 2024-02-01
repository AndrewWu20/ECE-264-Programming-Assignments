#ifndef __JSON_H__
#define __JSON_H__
#include <stdbool.h>

typedef struct {
	enum  { ELEMENT_INT, ELEMENT_STRING, ELEMENT_LIST } type;
	union {
		int    as_int;
		char*  as_string;
		struct _Node* as_list;
	}; // ANONYMOUS union (C11).
} Element;


typedef struct _Node {
	struct _Node* next;
	Element element;
} Node;

typedef struct {
	bool is_success;
	union {
		Element element;
		long int idx;
	};
}ParseResult;  // TODO:  make this into a struct type definition

bool parse_int(int* a_value, char const** a_pos);
bool parse_string(char** a_s, char const** a_pos);
bool parse_element(Element* a_element, char const** a_pos);
bool parse_list(Node** a_head, char const** a_pos);
void print_element(Element element);
void free_element(Element element);
ParseResult parse_json(char const* json);

#endif

#define JSON_H_VERSION_2
/* vim: set tabstop=4 shiftwidth=4 fileencoding=utf-8 noexpandtab: */
