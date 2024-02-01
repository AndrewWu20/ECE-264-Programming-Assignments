#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include "huffman.h"

static int _compare_func(const void*, const void*);								//Helper function declaration

static int _compare_func(const void* void_next, const void* void_curr) {		//Compare helper function
	TreeNode const* new = void_next;											//Declarations for TreeNode and integer variables
	TreeNode const* current = void_curr;
	int current_value = (int)(((TreeNode*)void_curr) -> frequency);
	int compare_value = (int)(((TreeNode*)void_next) -> frequency);
	int result = 0;

	if (current_value > compare_value) {										//Add one to frequency if the value being compared is less than the current value in the list
		result = 1;
	}
	else if (current_value < compare_value) {									//Subtract one from frequency if the value is being compared is greater than the current value in the list
		result = -1;
	}
	
	else if (current_value == compare_value) {									//If the values are equal, place the character with a lesser ASCII value first
		if(new -> character > current -> character) {
			result = -1;
		}
	}
	return result;
}

Node* make_huffman_pq(Frequencies freqs) {										//Makes the list for values to be placed into
	Node* node = NULL;
	for(int i = 0; i < 256; i++) {
		if(freqs[i] != 0) {
			TreeNode* tree = malloc(sizeof(*tree));
			*tree = (TreeNode) { .character = i, .frequency = freqs[i], .character = i, .left = NULL, .right = NULL};
			pq_enqueue(&node, tree, _compare_func);
		}
	}
	return node;
}
/* vim: set tabstop=4 shiftwidth=4 fileencoding=utf-8 noexpandtab: */
