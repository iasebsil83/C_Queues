// ---------------- IMPORTATIONS ----------------

//standard
#include <stdio.h>
#include <stdlib.h>

//to add text elements
#include <string.h>

//enable internal errors (stability over performance)
//#define INTERNAL_ERRORS

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
	puts("I.A. > This is an example of using queues in C with \"queues.c/.h\".\n");



	//CREATE

	//create a queue
	puts("I.A. > Creating a queue...");
	queue* myQ = queue_create();
	printf("I.A. > Queue created (length %u).\n", myQ->length);



	//ADD ELEMENTS

	//add an integer value
	int i = -12;
	printf("I.A. > Adding integer %i to queue.\n", i);
	queue_append(myQ, &i, sizeof(i));

	//add a long long number
	long long l = 123456789012345678;
	printf("I.A. > Adding long long %lld to queue.\n", l);
	queue_append(myQ, &l, sizeof(l));

	//add a string
	char s[]   = "Hello there !";
	int  s_len = strlen(s);                               //exactly like storing a regular character
	printf("I.A. > Adding string \"%s\" to queue.\n", s); //but the size is greater. So more than 1
	queue_append(myQ, s, s_len);                          //character will be stored.

	//add a single character
	char c = '_';
	printf("I.A. > Adding character '%c' to queue.\n", c);
	queue_append(myQ, &c, sizeof(c));
	printf("I.A. > Now, queue length is %u.\n", myQ->length);



	//SHOW

	//show each elements
	int*       i_ptr = queue_get(myQ, 0);
	printf("I.A. > Element index 0 of queue is an integer  : %i.\n", *i_ptr);
	long long* l_ptr = queue_get(myQ, 1);
	printf("I.A. > Element index 1 of queue is a long long : %lld.\n", *l_ptr);
	char*      s_ptr = queue_get(myQ, 2);
	printf("I.A. > Element index 2 of queue is a string    : \"%.*s\".\n", s_len, s_ptr);
	char*      c_ptr = queue_get(myQ, 3);
	printf("I.A. > Element index 3 of queue is a character : %c.\n", *c_ptr);



	//DELETE

	//clearing queue
	puts("I.A. > Clearing queue...");
	queue_clear(myQ);
	printf("I.A. > Queue cleared (length %u).\n", myQ->length);



	return EXIT_SUCCESS;
}
