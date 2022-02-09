#Variables

CFLAGS = -Wall -pedantic -g
OBJ = date.o list.o input.o coronablinker.o

#Targets

date.o: date.c date.h
	gcc $(CFLAGS) -c date.c -o date.o

list.o: list.c list.h date.h
	gcc $(CFLAGS) -c list.c -o list.o

input.o: input.c date.h
	gcc $(CFLAGS) -c input.c -o input.o

coronablinker.o: coronablinker.c date.h list.h input.h
	gcc $(CFLAGS) -c coronablinker.c -o coronablinker.o

coronablinker.exe: date.o list.o input.o coronablinker.o
	gcc $(CFLAGS) $(OBJ) -o coronablinker

