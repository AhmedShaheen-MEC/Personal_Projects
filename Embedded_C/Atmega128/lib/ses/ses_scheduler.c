/*INCLUDES ************************************************************/
#include "ses_timer.h"
#include "util/atomic.h"
#include "ses_scheduler.h"

/* PRIVATE VARIABLES **************************************************/
/** list of scheduled tasks */
static taskDescriptor* taskList = NULL; // Head node.


/*FUNCTION DEFINITION *************************************************/

static void scheduler_update(void) 
{
	// set the head node address and loop throgh the list.
	taskDescriptor* head = taskList;
	ATOMIC_BLOCK(ATOMIC_RESTORESTATE) 
	{
		while (head != NULL)
		{	
			
			if (head->expire == 0) 
			{
				head->execute = 1;
				head->expire = head->period; 
			}
			head->expire = (head->expire) - 1; // subtract ms (each firing of the timer2)
			head = head->next;
		}
	}
}

void scheduler_init() 
{
	// init time 2 and set call back
	timer2_setCallback(&scheduler_update);
	timer2_start();
}

void scheduler_run() 
{
	taskDescriptor * task_address;
	while (1)
	{	
	 	ATOMIC_BLOCK(ATOMIC_RESTORESTATE) 
	 	{
			 while (task_address != NULL)
	 		{
				 // loop through each task
				if( (task_address->execute) == 1)
	 			{	
					 break;	
	 			}
	 			task_address = task_address->next;
	 		}
		}
	 	// check weither the task is periodic or not
		if ((task_address) == NULL)
		{
			// the loop has finished, reset
			task_address = taskList;
			
		}	
		// if execute == 1 check for periodicity
	 	else if ((task_address->period) > 1 ) 
	 	{
	 		task_address->task(task_address->param); // execute the periodic tasks
	 		task_address->execute = 0;	
			task_address = task_address->next;	
			
		}	
	 	else if ((task_address->period)  == 0)
		{	
	 		task_address->task(task_address->param); 
	 		scheduler_remove(task_address);
		 	task_address = task_address->next;	
	 	} 	
		
	}
}


bool scheduler_add(taskDescriptor * toAdd)
{
	// the  head was NULL at the begining,
	//advacing in time the head changes but the next (last) task will point to NULL as well.
	// make sure that the adding process not interrupted.
	ATOMIC_BLOCK(ATOMIC_RESTORESTATE) 
	{
		taskDescriptor * holder = taskList;
		if (toAdd == NULL)
		{
			return false;
		}
		// check if its already in the list
		while(holder != NULL)
		{
			if ( holder == toAdd)
			{
				return false;
			}
			holder = holder->next;
		}
		toAdd->next = taskList;		
		taskList = toAdd;
	}
	return true;
} 			

void scheduler_remove(taskDescriptor * toRemove) 
{
	taskDescriptor * right;
	taskDescriptor * left;
	ATOMIC_BLOCK(ATOMIC_RESTORESTATE) 
	{
		right = toRemove->next;
		left = taskList;
		// find the left node. 
		while (left != NULL)
		{
			if (left->next == toRemove)
			{
				break;
			}
			left = left->next;
		}
		// make sure that the removing process not interrupted.
		if( toRemove == taskList) // if the head node wanted to be removed
		{
			// set the head to the next task
			taskList = toRemove->next;
		}
		else
		{
			left->next = right;
		}
	}
	
}
