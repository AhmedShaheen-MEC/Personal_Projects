/*
 * linked_list.c
 *
 *  Created on: Oct 21, 2020
 *      Author: ahmed
 */
/*INCLUDES ************************************************************/
#include "linked_list.h"

/*FUNCTION DEFINITION *************************************************/

int sorted_list_insert(tstr_node **head , tstr_node *pstr_node)
{
	// Check if null
	if (pstr_node == NULL)
	{
		// input node pointer was not initialized
		return false;
	}
	// if the list was empty
	if (*head == NULL)
	{
		*head = pstr_node;
		pstr_node->next = NULL;
		return true;
	}
	// allocate the node according to string ASCII values
	return compare_string(head,pstr_node);
}

int sorted_list_remove(tstr_node **ppstr_head , tstr_node *pstr_node)
{
	// Copy the head node value
	tstr_node * current_node = *ppstr_head ;
	if (pstr_node == NULL)
	{
		return false;
	}
	// if removing the head node
	if (current_node == pstr_node)
	{
		*ppstr_head = current_node->next;
		free(current_node);
		return true;
	}
	// find the left node.
	while (current_node != NULL)
	{
		if (current_node->next == pstr_node)
		{
			break;
		}
		current_node = current_node->next;
	}
	if (current_node == NULL) 			// node is not in the list
	{
		return false; 					// return and do not change any thing
	}
	current_node->next = pstr_node->next;
	free(pstr_node);
	return true;
}

int compare_string(tstr_node **head , tstr_node *pstr_node)
{
	tstr_node * current_node = *head;			// Copy the head node address
	tstr_node * prev;							// declare a temporary variable
	while(current_node != NULL)					// Loop through the list
	{
		// search for the right place
		if (strcmp(pstr_node->data, current_node->data) > 0)
		{
			prev = current_node;				// Copy the previous value in case if needed
			current_node= current_node->next;
			continue;
		}
		//place the string just before the larger string
		pstr_node->next = current_node;
		//If the next was the head, rearrange the addresses
		if(pstr_node->next == *head)
		{
			prev = (*head);						// Use the temp variable to preserve the address of the head node
			(*head) = pstr_node;				// Head node points to the smallest variable
			(*head)->next = prev;
			return true;
		}
		prev->next= pstr_node;					// Set the previous to point to the newly added node
		return true;
	}
	// current node was NULL, the newly added node has the largest value in the list
	prev->next= pstr_node;
	pstr_node->next = NULL;
	return true;
}

void display_list(tstr_node **head)
{
	tstr_node *current_node = *head;
	int i = 0;
	while(current_node != NULL)
	{
		printf("String number %d is: %s \n",i, current_node->data);
		current_node = current_node->next;
		i++;
	}
	printf("Finished...!\n");
}
