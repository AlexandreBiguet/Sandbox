
GCC = gcc -Wextra -Wall -std=gnu99 -fnested-functions -W -fshort-enums -g -O2


FLAGS = -lgsl -lgslcblas -g

all: prog

main.o: main.c
	$(GCC) -c -o main.o main.c


prog: main.o
	$(GCC) -o prog main.o $(FLAGS)

clean:
	rm -f *.o