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

	if(current_value > compare_value) {										//Add one to frequency if the value being compared is less than the current value in the list
		result = 1;
	}
	else if(current_value < compare_value) {									//Subtract one from frequency if the value is being compared is greater than the current value in the list
		result = -1;
	}
	else if(current_value == compare_value) {									//If the values are equal, place the character with a lesser ASCII value first
		if((new -> character) > (current -> character)) {
			result = -1;
		}
	}
	if(((current -> frequency) == (new -> frequency)) && ((new -> character) == '\0')) {
		result = -1;
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

TreeNode* make_huffman_tree(Node* head) {
	if(head == NULL) {
		return NULL;
	}
	while(head -> next != NULL) {
		TreeNode* cluster = malloc(sizeof(*cluster));			//Creates memory for cluster	//Valgrind error, thinking that I don't free cluster?
		TreeNode* tree_value = head -> a_value;					//TreeNode variables
		TreeNode* tree_next_value = head -> next -> a_value;
		*cluster = (TreeNode) { .character = '\0', .left = head -> next -> a_value, .right = head -> a_value, .frequency = (tree_value -> frequency) + (tree_next_value -> frequency) };									//Compound literal for cluster	
		free(pq_dequeue(&head));
		free(pq_dequeue(&head));
		pq_enqueue(&head, cluster, _compare_func);
	}
	TreeNode* new_value = head -> a_value;						//Create a temporary variable so head can be freed
	free(head);
	return new_value;
}

void destroy_huffman_tree(TreeNode** a_root) {
	if(*a_root != NULL) {									//If the root is not null, call destroy function to destroy the left and right nodes
		destroy_huffman_tree(&(*a_root) -> left);
		destroy_huffman_tree(&(*a_root) -> right);
		free(*a_root);
	}
	*a_root = NULL;
}
/* vim: set tabstop=4 shiftwidth=4 fileencoding=utf-8 noexpandtab: */
