// ---------------- IMPORTATIONS ----------------

//standard
#include <stdio.h>
#include <stdlib.h>




//own header
#include "queues.h"








/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Queues [0.1.0] ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                                 Queues by I.A.

        Queues is an utility program that allows you to create and manipulate
    queues of any type (fixed type recommended).

        Theses queues are working as simple linked lists. Therefore, queues
    lengths are dynamic so make sure to check it via queue_length(). Also,
    some functions are using (queue**) instead of (queue*) so make sure to
    give the correct reference.
    (queue** is required when queue head can change.)

        As last point, some functions are using recursivity to work (for
    optimization). So there is ONE rule to keep in mind :

        ------------------------------------------
        /!\ DO NOT TURN A QUEUE INTO A CYCLE* ! /!\
        ------------------------------------------

    *(a cycle is a queue which has its last element pointing to its first)

    DISCLAIMER about mixed types :
        If you want to use different types in the same queue, you will have
        to remember :

        - The size of each data in the queue.
          (No problem if they all have the same size)
        - The type each value refers to.
          (the first one is a float, the second one is an int, ...)

    22/01/2021 > [0.1.0] :
    - Created queues.c/.h.

    BUGS : .
    NOTES : .

    Contact     : i.a.sebsil83@gmail.com
    Youtube     : https://www.youtube.com/user/IAsebsil83
    GitHub repo : https://github.com/iasebsil83

    Let's Code !                                  By I.A.
******************************************************************************************

    LICENCE :

    C_Queues
    Copyright (C) 2021  Sebastien SILVANO
    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    any later version.
    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.
    You should have received a copy of the GNU General Public License
    along with this program.

    If not, see <https://www.gnu.org/licenses/>.
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */








// ---------------- INSTANTIATION ----------------

//create - delete - length
#define MEMORY_COPY_FROM_A_TO_B(A,B,size) \
	for(unsigned int u=0; u < size; u++){ \
		( (char*)(B) )[u] = ( (char*)(A) )[u]; \
	}

queue* queue_create(void* data, unsigned int size){ //data used will no longer stay inside queue, it will be copied

	//error cases
	if(data == NULL || size == 0){
		printf("RUNTIME ERROR > queues.c : queue_create() : Data is NULL or size is equal to 0.\n.");
		return NULL;
	}

	//create queue
	queue* q = malloc(sizeof(queue));
	if(q == NULL){
		printf("FATAL ERROR > queues.c : queue_create() : Computer refuses to give more memory.\n.");
		exit(EXIT_FAILURE);
	}

	//set size
	q->size = size;

	//set data (copy)
	q->data = malloc(q->size);
	if(q->data == NULL){
		printf("FATAL ERROR > queues.c : queue_create() : Computer refuses to give more memory.\n.");
		exit(EXIT_FAILURE);
	}
	MEMORY_COPY_FROM_A_TO_B(data, q->data, q->size);
	q->next = NULL;

	return q;
}

unsigned int queue_length(queue* q){ // WARNING ! Can cause infinite loop if queue is a cycle !

	//empty queue
	if(q == NULL){
		return 0;
	}

	//not empty queue
	unsigned int length = 1;
	while(q->next != NULL){
		length++;
		q = q->next;
	}

	return length;
}

static void queue_removeAll(queue* q){

	//error cases
	if(q == NULL){
		printf("RUNTIME ERROR > queues.c : queue_delete() : Queue is NULL.\n");
		return;
	}

	//recursive remove (from last to first)
	if(q->next != NULL){
		queue_removeAll(q->next);
	}

	//free element
	if(q->data != NULL){
		free(q->data);
	}
	free(q);
}

void queue_delete(queue** q){ // WARNING ! Can cause free overlap if queue is a cycle !
	queue_removeAll(*q);
	*q = NULL;
}








// ---------------- USE ----------------

//get - set
queue* queue_get(queue* q, unsigned int index){

	//error cases
	if(q == NULL){
		printf("RUNTIME ERROR > queues.c : queue_get() : Queue is NULL.\n");
		return NULL;
	}

	//iterate until the correct q is found
	unsigned int i = 0;
	while(i != index){
		i++;

		//error case
		if(q == NULL){
			printf("RUNTIME ERROR : queues.c : queue_get() : Index %u is too big.\n", index);
			return NULL;
		}
		q = q->next;
	}

	//correct element found
	return q;
}

void queue_set(queue* q, unsigned int index, void* data, unsigned int size){ //data used will no longer stay inside queue, it will be copied

	//error cases
	if(q == NULL){
		printf("RUNTIME ERROR > queues.c : queue_set() : Queue is NULL.\n");
		return;
	}
	if(data == NULL || size == 0){
		printf("RUNTIME ERROR > queues.c : queue_set() : Data is NULL or size equal to 0.\n");
		return;
	}

	//get concerned element
	queue* q_sel = queue_get(q, index);
	if(q_sel == NULL){
		printf("RUNTIME ERROR > queues.c : queue_set() : Could not get data at specified index %u.\n", index);
		return;
	}

	//correct element found
	if(q_sel->data != NULL)
		free(q_sel->data); //free contained data (if existing)

	//set new size
	q_sel->size = size;

	//set new data (copy)
	q_sel->data = malloc(q_sel->size);
	if(q_sel->data == NULL){
		printf("FATAL ERROR > queues.c : queue_set() : Computer refuses to give more memory.\n");
		exit(EXIT_FAILURE);
	}
	MEMORY_COPY_FROM_A_TO_B(data, q_sel->data, q_sel->size);
}




//add - remove
void queue_addBeforeFirst(queue** q, void* data, unsigned int size){ //data used will no longer stay inside queue, it will be copied
                                                                     //WARNING ! Queue head may change !
	//error cases
	if(q == NULL || *q == NULL){
		printf("RUNTIME ERROR > queues.c : queue_addBeforeFirst() : Queue or queue pointer is NULL.\n");
		return;
	}
	if(data == NULL || size == 0){
		printf("RUNTIME ERROR > queues.c : queue_addBeforeFirst() : Data is NULL or size equal to 0.\n");
		return;
	}

	//create new element (new queue head)
	queue* q_new = malloc(sizeof(queue));
	if(q_new == NULL){
		printf("FATAL ERROR > queues.c : queue_addBeforeFirst() : Computer refuses to give more memory.\n.");
		exit(EXIT_FAILURE);
	}

	//set size
	q_new->size = size;

	//set data
	q_new->data = malloc(q_new->size);
	if(q_new->data == NULL){
		printf("FATAL ERROR > queues.c : queue_addBeforeFirst() : Computer refuses to give more memory.\n.");
		exit(EXIT_FAILURE);
	}
	MEMORY_COPY_FROM_A_TO_B(data, q_new->data, q_new->size);

	//set next
	q_new->next = *q;

	//set new queue head
	*q = q_new;
}

void queue_addAfter(queue* q, unsigned int index, void* data, unsigned int size){ //data used will no longer stay inside queue, it will be copied

	//error cases
	if(q == NULL){
		printf("RUNTIME ERROR > queues.c : queue_addAfter() : Queue is NULL.\n");
		return;
	}
	if(data == NULL || size == 0){
		printf("RUNTIME ERROR > queues.c : queue_addAfter() : Data is NULL or size equal to 0.\n");
		return;
	}

	//create new element
	queue* q_new = malloc(sizeof(queue));
	if(q_new == NULL){
		printf("FATAL ERROR > queues.c : queue_addAfter() : Computer refuses to give more memory.\n.");
		exit(EXIT_FAILURE);
	}

	//set size
	q_new->size = size;

	//set data
	q_new->data = malloc(q_new->size);
	if(q_new == NULL){
		printf("FATAL ERROR > queues.c : queue_addAfter() : Computer refuses to give more memory.\n.");
		exit(EXIT_FAILURE);
	}
	MEMORY_COPY_FROM_A_TO_B(data, q_new->data, q_new->size);

	//get the element before the new (in position #index#)
	queue* q_before = queue_get(q, index);
	if(q_before == NULL){
		printf("RUNTIME ERROR > queues.c : queue_addAfter() : Could not get data at specified index %u.\n", index);
		return;
	}

	//get the element after the new (in position #index#+1)
	queue* q_after = q_before->next;

	//attach the 2 sides of the new element
	q_before->next = q_new;
	q_new->next    = q_after;
}

void queue_remove(queue** q, unsigned int index){ //WARNING ! Queue head may change !

	//error cases
	if(q == NULL || *q == NULL){
		printf("RUNTIME ERROR > queues.c : queue_remove() : Queue or queue pointer is NULL.\n");
		return;
	}

	//first case : first element of queue
	if(index == 0){

		//get the 2nd element
		queue* q_2nd = (*q)->next;

		//remove the first one
		if( (*q)->data != NULL){
			free( (*q)->data );
		}
		free(*q);

		//attach new head
		*q = q_2nd;
	}

	//other cases
	else{

		//get the element before the one to remove (in position #index#-1)
		queue* q_before = queue_get(*q, index);

		//get the element to remove
		queue* q_toRemove = q_before->next;
		if(q_toRemove == NULL){
			printf("RUNTIME ERROR > queues.c : queue_remove() : No element at index %u.\n", index);
			return;
		}

		//get the element after the one to remove (in position #index#+1)
		queue* q_after = q_before->next;

		//attach the previous element to the next (skip the one to remove)
		q_before->next = q_after;

		//free the selected element
		if(q_toRemove->data != NULL){
			free(q_toRemove->data);
		}
		free(q_toRemove);
	}
}
#undef MEMORY_COPY_FROM_A_TO_B
