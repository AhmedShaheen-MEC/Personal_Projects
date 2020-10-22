#ifndef LINKD_LIST_H_
#define LINKD_LIST_H_

/*INCLUDES *******************************************************************/
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
/* TYPES ********************************************************************/

#define MAX_STRING_LENGTH 80
#define false -1
#define true 0

typedef struct string_node{

	char data[MAX_STRING_LENGTH];	// Holds strings value of the node
	struct string_node * next;		// Points to the next node which has a larger value strings

}tstr_node;

/* FUNCTION PROTOTYPES *******************************************************/

/**
 * This function inserts a new node to the list in the correct place, so the list
 * remain sorted.
 * @param head A pointer which points to the head node pointer
 * @param pstr_node a pointer to the data structure node which should be added
 *
 * @return either 0 if succeeded or -1 if failed
 */
int sorted_list_insert(tstr_node **head , tstr_node *pstr_node);

/**
 * This function removes a certain node only if the node is in the list.
 * @param head A pointer which points to the head node pointer
 * @param pstr_node a pointer to the data structure node which should be added
 *
 * @return either 0 if succeeded or -1 if failed
 */
int sorted_list_remove(tstr_node **ppstr_head , tstr_node *pstr_node);

/**
 * This function compare the value stored in the "data" member of each node in the list
 * and decide on the correct location which should used for placement.
 *
 * @return either 0 if succeeded or -1 if failed
 */
int compare_string();

/**
 * This function displays all the data stored in each node in the list.
 */
void display_list(tstr_node **head);

#endif /* LINKD_LIST_H_ */
