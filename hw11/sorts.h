#include <stdlib.h>
#ifndef __SORTS_H__
#define __SORTS_H__

typedef struct _BSTNode {
	int value;
	struct _BSTNode* left;
	struct _BSTNode* right;
} BSTNode;

typedef struct _BST {
	BSTNode *root;
	int size;
} BST;

BST create_bst(const int* array, int size);
void empty_bst(BST* bst);
void tree_sort_array(int* array, size_t size);
#endif
/* vim: set tabstop=4 shiftwidth=4 fileencoding=utf-8 noexpandtab: */
