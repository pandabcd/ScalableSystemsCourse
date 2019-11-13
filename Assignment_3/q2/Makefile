CC=mpicc

all: temp 

temp: temp.o
	$(CC) -o temp temp.o 

temp.o: temp.c
	$(CC) -o temp.o -c temp.c

clean:
	rm -f temp.o temp