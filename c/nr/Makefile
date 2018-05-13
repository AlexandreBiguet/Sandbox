all:NR

GCC := gcc -Wextra -Wall -std=gnu99 -fnested-functions

OBJ := main.o nr-routines.o test.o

NR: ${OBJ}
	${GCC} -o NR ${OBJ} #-lgsl -lgslcblas

main.o: main.c
	${GCC} -c -o main.o main.c

nr-routines.o: nr-routines.c
	${GCC} -c -o nr-routines.o nr-routines.c

test.o: test.c
	${GCC} -c -o test.o test.c
	
clean:
	rm -f *.o