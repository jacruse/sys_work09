run: all
	./run

all: dir.o
	gcc -o run dir.o 

dir.o: dir.c
	gcc -c dir.c

clean:
	rm -rf *~
	rm -rf *.o
	rm run
