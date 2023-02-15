// ---------------- IMPORTATIONS ----------------

//standard
#include <stdio.h>
#include <stdlib.h>




//queues utility
#include "../lib/queues.h"








/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Prog [V.V.V] ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                        queues.h demonstration program

        Blablabla about the subject.

    DD/MM/YYYY > [V.V.V] :
    - Added something.
    - Added something else.

    DD/MM/YYYY > [V.V.V] :
    - Added something that wasn't before.
    - Fixed a bug.
    - Added something else.
    - Added something else again.

    BUGS : Active bugs in last version.
    NOTES : Notes.

    Contact     : ...
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */








// ---------------- EXECUTION ----------------

//main
int main(){

	//presentation
	printf("I.A. > This is an example of using queues in C with \"queues.c/.h\".\n\n");



	//CREATE

	//create a queue
	printf("I.A. > Creating an int queue with -20 as first element...\n");
	int start = -20;
	queue* intQueue = queue_create(&start, sizeof(start));
	printf("I.A. > Queue created.\n");

	//getting queue length
	unsigned int len = queue_length(intQueue);
	printf("I.A. > Queue length is %u.\n", len);



	//ADD ELEMENTS

	//add some elements to queue
	for(int i=-12; i < 21; i++){

		//add
		printf("I.A. > Adding %i to queue.\n", i);
		queue_append(intQueue, &i, sizeof(i));

		//check length
		len = queue_length(intQueue);
		printf("I.A. > Now, queue length is %u.\n", len);
	}



	//SHOW

	//show each elements
	queue* tempQ;
	for(unsigned int ui=0; ui < len; ui++){

		//get queue element at index #ui#
		tempQ = queue_get(intQueue, ui);
		if(tempQ == NULL){
			continue;
		}
		printf("I.A. > Element %u of queue is %i.\n", ui, *( (int*)(tempQ->data) ) );
	}



	//DELETE

	//deletting queue
	printf("I.A. > Deletting queue...\n");
	queue_delete(&intQueue);
	printf("I.A. > Queue deleted.\n");

	//check length
	printf("I.A. > Now queue length is %u.\n", queue_length(intQueue));



	return EXIT_SUCCESS;
}
