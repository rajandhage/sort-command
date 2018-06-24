project: main.o list.o 
	cc main.o list.o -o project
main.o: main.c list.o 
	cc -c main.c
list.o: list.c list.h  
	cc -c list.c
clean: 
	rm *.o
