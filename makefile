#executable
run: queues.o prog.o
	gcc -Wall -o run prog.o queues.o -O2
	rm -f *.o



#example program
prog.o: src/prog.c lib/queues.h
	gcc -Wall -c src/prog.c -O2



#queues library
queues.o: lib/queues.c lib/queues.h
	gcc -Wall -c lib/queues.c -O2
