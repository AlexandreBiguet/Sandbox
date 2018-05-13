all:GSL

GCC := gcc -Wextra -Wall -std=gnu99 -fnested-functions

OBJ := main.o GSL-routines.o test.o utils.o

GSL: ${OBJ}
	${GCC} -o GSL ${OBJ} -lgsl -lgslcblas

main.o: main.c
	${GCC} -c -o main.o main.c
	
GSL-routines.o: GSL-routines.c
	${GCC} -c -o GSL-routines.o GSL-routines.c
	
test.o: test.c
	${GCC} -c -o test.o test.c

utils.o: utils.c
	${GCC} -c -o utils.o utils.c
	
clean:
	rm -f *.o