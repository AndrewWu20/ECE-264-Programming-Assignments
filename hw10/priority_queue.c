#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include "priority_queue.h"


Node* pq_enqueue(Node** a_head, void* a_value, int (*cmp_fn)(void const*, void const*)) {
	Node* new_node = malloc(sizeof(*new_node));				//Malloc an empty node
	*new_node = (Node) {.a_value = a_value, .next = NULL};
	
	if (*a_head == NULL || (cmp_fn((*a_head) -> a_value, (new_node -> a_value)) > 0)) {						//Check if a_head is null
		Node *temp_address = (*a_head);			//Sets value of next head to the old head
		(*a_head) = new_node;						
		new_node -> next = temp_address;
	}
	else {
		Node* current_address = *a_head;
		while(current_address -> next != NULL && cmp_fn(current_address -> next -> a_value, (new_node -> a_value)) <= 0) {	//Goes through node and moves address of node forwards given that the current node is greater than the next and if it isn't at the end of the list
			current_address = current_address -> next;
		}
		new_node -> next = (current_address -> next);	//Inserts a new node
		current_address -> next = new_node;

	}	
	
	return new_node;
}


Node* pq_dequeue(Node** a_head) {
	Node* remove_node = (*a_head);				//Store address
	if (a_head != NULL) {
		(*a_head) = (*a_head) -> next;				//Reference next node in list
		remove_node -> next = NULL;					//Sets the next field of remove_node equal to null
	}

	return remove_node;  
}


Node* stack_push(Node** a_head, void* a_value) {
	return pq_enqueue(a_head, a_value, NULL);	//Push list to create space at the front of the list
}


Node* stack_pop(Node** a_head) {
	return pq_dequeue(a_head); 					//Remove first position of list
}


void destroy_list(Node** a_head, void (*destroy_value_fn)(void*)) {		
	while (*a_head != NULL) {
		Node* destroy = (*a_head) -> next;		//Assign destroy to value of address after a_head
		free(*a_head);							//Free up memory
		*a_head = destroy;						//Reassign a_head to value of next address
	}
}


#define HUFFMAN_C_V1
