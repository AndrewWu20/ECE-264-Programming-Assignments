#include <stdio.h>									
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include "sorts.h"

static void _insert(int value, BSTNode** a_root) { 			//Helper function that will insert nodes into a binary search tree
	if(*a_root == NULL) {									//If the root is equal to null, make any values added have the root's address
		BSTNode* new_node = malloc(sizeof(*new_node));
		*new_node = (BSTNode) { .value = value, .left = NULL, .right = NULL};	//Declaration and initialization of the new node

		*a_root = new_node;
	}
	else if(value < ((*a_root) -> value)) {
		_insert(value, &((*a_root) -> left));
	}
	else {
		_insert(value, &((*a_root) -> right));
	}
}

static void _destroy_bst(BSTNode** a_root) {	//Helper function that destroys the binary search tree
	if(*a_root != NULL) {
		_destroy_bst(&(*a_root) -> left);	//This line and the next recurrsively calls the destroy function for both branches stemming off of the root
		_destroy_bst(&(*a_root) -> right);
		free(*a_root);
	}

	*a_root = NULL;
}

static void _fill_array_from_bst(int* a_root_value, BSTNode* root, int *position_of_value_in_array) {	//Helper function that fills an array in numeric order from the binary search tree 
	if(root != NULL) {
		_fill_array_from_bst(a_root_value, root -> left, position_of_value_in_array);
		*(a_root_value + (*position_of_value_in_array)++) = root -> value; //Sets the next value in the array to be the smallest value in the tree
		_fill_array_from_bst(a_root_value, root -> right, position_of_value_in_array);
	}
}

BST create_bst(const int* array, int size) {				//Function that creates a binary search tree from an array
	BST created_bst = { .root = NULL, .size = size};		
	for(int i = 0; i < size; i++) {							//Loops through a BST to input values
		_insert(array[i], &created_bst.root);
	}
	return created_bst;
}

void empty_bst(BST* delete_bst) {							//Function that clears a binary search tree
	_destroy_bst(&delete_bst -> root);
}

void tree_sort_array(int* array, size_t size) {				//Function that sorts a given array
	int position_of_value_in_array = 0;
	BST bst = create_bst(array, size);
	_fill_array_from_bst(array, bst.root, &position_of_value_in_array);		//Returns sorted values from the original BST back into the original BST
	empty_bst(&bst);	
}

/* vim: set tabstop=4 shiftwidth=4 fileencoding=utf-8 noexpandtab: */
