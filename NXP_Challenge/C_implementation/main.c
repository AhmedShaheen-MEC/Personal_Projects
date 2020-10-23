/*
 ============================================================================
 Name        : main.c, NXP_challenge
 Author      : Ahmed Shaheen
 Version     :
 Copyright   : Your copyright notice
 Description : String sorted linked list, Ansi-style
 ============================================================================
 */


#include "linked_list.h"

/* Define test cases for the linked list, functions used so that each test case done separately
*  free used to avoid memory leak.
*/
int test_add_largest_string(){

	// Prepare a test set
	tstr_node* head = NULL;
	tstr_node ** ptr_head = &head;
	tstr_node *s1,*s2, *s3;

	s1 = (tstr_node*)malloc(sizeof(tstr_node));
	s2 = (tstr_node*)malloc(sizeof(tstr_node));
	s3 = (tstr_node*)malloc(sizeof(tstr_node));


	// Provide each node with a certain string
	strcpy(s1->data,"ABC");
	strcpy(s2->data,"EFG");
	strcpy(s3->data,"HIJ");

	// Insert initial  nodes
	sorted_list_insert(ptr_head,s1);
	sorted_list_insert(ptr_head,s2);
	sorted_list_insert(ptr_head,s3);

	tstr_node *test_string;
	test_string = (tstr_node*)malloc(sizeof(tstr_node));
	strcpy(test_string->data,"zzz");

	printf("\n-----------------------------\n");
	printf("Test string: is %s\n\n", test_string->data);
	if (sorted_list_insert(ptr_head,test_string) == -1){

		return -1;
	}
	display_list(ptr_head);

	free(s1);
	free(s2);
	free(s3);
	free(test_string);

	return 0;
}

int test_add_smallest_string(){

	// Prepare a test set
	tstr_node* head = NULL;
	tstr_node ** ptr_head = &head;
	tstr_node *s1,*s2, *s3;

	s1 = (tstr_node*)malloc(sizeof(tstr_node));
	s2 = (tstr_node*)malloc(sizeof(tstr_node));
	s3 = (tstr_node*)malloc(sizeof(tstr_node));


	// Provide each node with a certain string
	strcpy(s1->data,"ABC");
	strcpy(s2->data,"EFG");
	strcpy(s3->data,"HIJ");

	// Insert initial  nodes
	sorted_list_insert(ptr_head,s1);
	sorted_list_insert(ptr_head,s2);
	sorted_list_insert(ptr_head,s3);

	tstr_node *test_string;
	test_string = (tstr_node*)malloc(sizeof(tstr_node));
	strcpy(test_string->data,"AAA");

	printf("\n-----------------------------\n");
	printf("Test string: is %s\n\n", test_string->data);
	if (sorted_list_insert(ptr_head,test_string) == -1){

		return -1;
	}
	display_list(ptr_head);

	free(s1);
	free(s2);
	free(s3);
	free(test_string);

	return 0;

}

int test_add_intermediate_string(){

	// Prepare a test set
	tstr_node* head = NULL;
	tstr_node ** ptr_head = &head;
	tstr_node *s1,*s2, *s3;

	s1 = (tstr_node*)malloc(sizeof(tstr_node));
	s2 = (tstr_node*)malloc(sizeof(tstr_node));
	s3 = (tstr_node*)malloc(sizeof(tstr_node));


	// Provide each node with a certain string
	strcpy(s1->data,"ABC");
	strcpy(s2->data,"Abc");
	strcpy(s3->data,"abc");

	// Insert initial  nodes
	sorted_list_insert(ptr_head,s1);
	sorted_list_insert(ptr_head,s2);
	sorted_list_insert(ptr_head,s3);

	tstr_node *test_string;
	test_string = (tstr_node*)malloc(sizeof(tstr_node));
	strcpy(test_string->data,"aBc");

	printf("\n-----------------------------\n");
	printf("Test string: is %s\n\n", test_string->data);
	if (sorted_list_insert(ptr_head,test_string) == -1){

		return -1;
	}
	display_list(ptr_head);

	free(s1);
	free(s2);
	free(s3);
	free(test_string);

	return 0;

}

int test_add_null(){

	// Prepare a test set
		tstr_node* head = NULL;
		tstr_node ** ptr_head = &head;
		tstr_node *s1,*s2, *s3;

		s1 = (tstr_node*)malloc(sizeof(tstr_node));
		s2 = (tstr_node*)malloc(sizeof(tstr_node));
		s3 = (tstr_node*)malloc(sizeof(tstr_node));


		// Provide each node with a certain string
		strcpy(s1->data,"ABC");
		strcpy(s2->data,"Abc");
		strcpy(s3->data,"abc");

		// Insert initial  nodes
		sorted_list_insert(ptr_head,s1);
		sorted_list_insert(ptr_head,s2);
		sorted_list_insert(ptr_head,s3);

		tstr_node *test_string;
		test_string = NULL;

		printf("\n-----------------------------\n");
		printf("Test string: is %d\n\n", test_string);
		if (sorted_list_insert(ptr_head,test_string) == 0){

			return -1;
		}
		display_list(ptr_head);

		free(s1);
		free(s2);
		free(s3);
		free(test_string);

		return 0;
}

int test_remove_null(){

	// Prepare a test set
	tstr_node* head = NULL;
	tstr_node ** ptr_head = &head;
	tstr_node *s1,*s2, *s3;

	s1 = (tstr_node*)malloc(sizeof(tstr_node));
	s2 = (tstr_node*)malloc(sizeof(tstr_node));
	s3 = (tstr_node*)malloc(sizeof(tstr_node));


	// Provide each node with a certain string
	strcpy(s1->data,"ABC");
	strcpy(s2->data,"Abc");
	strcpy(s3->data,"abc");

	// Insert initial  nodes
	sorted_list_insert(ptr_head,s1);
	sorted_list_insert(ptr_head,s2);
	sorted_list_insert(ptr_head,s3);

	tstr_node *test_string;
	test_string = NULL;

	printf("\n-----------------------------\n");
	printf("Test string: is %d\n\n", test_string);
	if (sorted_list_remove(ptr_head,test_string) == 0){
		return -1;
	}
	display_list(ptr_head);

	free(s1);
	free(s2);
	free(s3);
	free(test_string);

	return 0;
}

int test_remove_not_in_the_list(){

	// Prepare a test set
	tstr_node* head = NULL;
	tstr_node ** ptr_head = &head;
	tstr_node *s1,*s2, *s3;

	s1 = (tstr_node*)malloc(sizeof(tstr_node));
	s2 = (tstr_node*)malloc(sizeof(tstr_node));
	s3 = (tstr_node*)malloc(sizeof(tstr_node));


	// Provide each node with a certain string
	strcpy(s1->data,"ABC");
	strcpy(s2->data,"Abc");
	strcpy(s3->data,"abc");

	// Insert initial  nodes
	sorted_list_insert(ptr_head,s1);
	sorted_list_insert(ptr_head,s2);
	sorted_list_insert(ptr_head,s3);

	tstr_node *test_string;
	test_string = (tstr_node*)malloc(sizeof(tstr_node));
	strcpy(test_string->data,"New");

	printf("\n-----------------------------\n");
	printf("Test string: is %s\n\n", test_string->data);
	if (sorted_list_remove(ptr_head,test_string) == 0){
			return -1;
	}
	display_list(ptr_head);

	free(s1);
	free(s2);
	free(s3);
	free(test_string);

	return 0;
}

int test_sorting_order(){

	// Prepare a test set
	tstr_node* head = NULL;
	tstr_node ** ptr_head = &head;
	tstr_node *s1,*s2, *s3;

	s1 = (tstr_node*)malloc(sizeof(tstr_node));
	s2 = (tstr_node*)malloc(sizeof(tstr_node));
	s3 = (tstr_node*)malloc(sizeof(tstr_node));


	// Provide each node with a certain string
	strcpy(s1->data,"ABC");
	strcpy(s2->data,"Abc");
	strcpy(s3->data,"abc");

	// Insert initial  nodes
	sorted_list_insert(ptr_head,s1);
	sorted_list_insert(ptr_head,s2);
	sorted_list_insert(ptr_head,s3);
	strcpy(s3->data, "ABc");			// Change the value for testing purpose
	tstr_node * temp = head;
	printf("\n-----------------------------\n");
	while (temp->next != NULL)
	{
		if (strcmp(temp->data, temp->next->data) > 0)
			return -1;
		temp = temp->next;
	}

	display_list(ptr_head);

	free(s1);
	free(s2);
	free(s3);

	return 0;
}

int test_add_twice(){

	// Prepare a test set
	tstr_node* head = NULL;
	tstr_node ** ptr_head = &head;
	tstr_node *s1,*s2, *s3;

	s1 = (tstr_node*)malloc(sizeof(tstr_node));
	s2 = (tstr_node*)malloc(sizeof(tstr_node));
	s3 = (tstr_node*)malloc(sizeof(tstr_node));


	// Provide each node with a certain string
	strcpy(s1->data,"ABC");
	strcpy(s2->data,"EFG");
	strcpy(s3->data,"HIJ");

	// Insert initial  nodes
	sorted_list_insert(ptr_head,s1);
	sorted_list_insert(ptr_head,s2);
	sorted_list_insert(ptr_head,s3);

	printf("\n-----------------------------\n");
	if (sorted_list_insert(ptr_head,s1) == -1){
		return 0;
	}
	display_list(ptr_head);

	free(s1);
	free(s2);
	free(s3);

	return -1;
}

int main(void) {

	printf("Display test results:\n0: success\n-1:failure");
	printf("Add Largest number test: %d", test_add_largest_string());
	printf("Add smallest number test: %d", test_add_smallest_string());
	printf("Add intermediate number test: %d", test_add_intermediate_string());
	printf("Add null pointer test: %d", test_add_null());
	printf("Remove null pointer test: %d", test_remove_null());
	printf("Remove not in the list test: %d", test_remove_not_in_the_list());
	printf("Sorting order test %d", test_sorting_order());
	printf("Add the same node twice test: %d", test_add_twice());
	return 0;
}
