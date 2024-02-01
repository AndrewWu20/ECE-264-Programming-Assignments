#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include "sorts.h"

void _print_array(int* array, size_t size, const char* title) {
	printf("%s\n", title);
	for(int i = 0; i < size; i++) {
		printf("%d ", array[i]);
	}
	printf("\n\n");
}

int main(int argc, char* argv[]) {

	// Demonstrate create_bst(…)
	BST bst = create_bst((int[7]) { 4, 2, 6, 1, 3, 5, 7 }, 7);
	assert(bst.root        != NULL && bst.root->value        == 4);
	assert(bst.root->left  != NULL && bst.root->left->value  == 2);
	assert(bst.root->right != NULL && bst.root->right->value == 6);
	empty_bst(&bst);

	// Demonstrate tree_sort_array(…)
	int array1[] = { 5, 4, 2, 1, 7, 6, 3 };
	size_t size1 = sizeof(array1) / sizeof(*array1);  // # of elements
	_print_array(array1, size1, "Before tree_sort_array(array1)");
	tree_sort_array(array1, size1);
	_print_array(array1, size1, "After  tree_sort_array(array1)");

	// Demonstrate quick_sort_array(…)
	//
	// quick_sort_array(…) was removed for Spring 2022.
	//
	//int array2[] = { 5, 4, 2, 1, 7, 6, 3 };
	//size_t size2 = sizeof(array2) / sizeof(*array2);  // # of elements
	//_print_array(array2, size2, "Before quick_sort_array(array2)");
	//quick_sort_array(array2, size2);
	//_print_array(array2, size2, "After  quick_sort_array(array2)");

	return EXIT_SUCCESS;
}
#define DEMO_SORTS_VERSION_2
/* vim: set tabstop=4 shiftwidth=4 fileencoding=utf-8 noexpandtab: */
