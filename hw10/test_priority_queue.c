#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "priority_queue.h"
#include "miniunit.h"

static int _test_stack_push() {
	mu_start();
	//
	Node* a_top = NULL;
	int x = 1;
	stack_push(&a_top, &x);				//Pushes a_top using stack push
	mu_check(a_top -> a_value == &x);		//Checks the value of a_top
	destroy_list(&a_top, NULL);			//Destroys the node
	//
	mu_end();
	
}

static int _test_list_null() {
	mu_start();
	//
	Node* head = NULL;
	int value = 10;
	stack_push(&head, &value);				//Pushes head and value via stack push
	free(stack_pop(&head));
	mu_check(head == NULL);					//Checks if head is null
	
	destroy_list(&head, NULL);					//Destroys node
	mu_check(head == NULL);					//Check if the list is destroyed
	//
	mu_end();
}

/*static int _test_list_valid() {
	mu_start();
	//
	Node* head = 8;
	int value = 9;
	stack_push(&head, &value);
	free(stack_pop(&head));
	mu_check(head == NULL);

	destroy_list(&head, NULL);
	mu_check(head == NULL);
	//
	mu_end();
}*/

int main (int argc, char* argv[]) {
	mu_run(_test_stack_push);				//Run _test_stack_push
	mu_run(_test_list_null);				//Run _test_list_null
//	mu_run(_test_list_valid);

	return EXIT_SUCCESS;
}


