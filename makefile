#executable
run: queues.o prog.o
	gcc -Wall -o run prog.o queues.o -O2
	rm -f *.o



#example program
prog.o: prog.c queues.h
	gcc -Wall -c prog.c -O2



#queues library
queues.o: queues.c queues.h
	gcc -Wall -c queues.c -O2
