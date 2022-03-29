#Variables

CFLAGS = -Wall -pedantic -g
OBJ = date.o list.o input.o heap.o coronablinker.o devicepair.o
TESTOBJ = datetest.o listtest.o heaptest.o
BIN = coronablinker.exe datetest.exe listtest.exe heaptest.exe

#Opearting system dependent variables
ifeq ($(OS), Windows_NT)
RM = del
BIN = coronablinker.exe datetest.exe listtest.exe heaptest.exe
else
RM = rm
BIN = coronablinker datetest listtest heaptest
endif
#Targets

date.o: date.c date.h
	gcc $(CFLAGS) -c date.c -o date.o

list.o: list.c list.h date.h
	gcc $(CFLAGS) -c list.c -o list.o

devicepair.o: devicepair.c devicepair.h date.h
	gcc $(CFLAGS) -c devicepair.c -o devicepair.o

heap.o: heap.c heap.h date.h devicepair.h
	gcc $(CFLAGS) -c heap.c -o heap.o

input.o: input.c date.h
	gcc $(CFLAGS) -c input.c -o input.o

coronablinker.o: coronablinker.c date.h list.h input.h heap.h devicepair.h
	gcc $(CFLAGS) -c coronablinker.c -o coronablinker.o

coronablinker.exe: date.o list.o input.o coronablinker.o heap.o devicepair.o
	gcc $(CFLAGS) $(OBJ) -o coronablinker

clean: 
	$(RM) $(OBJ) $(TESTOBJ) $(BIN)

all: coronablinker.exe listtest.exe datetest.exe heaptest.exe

#Test targets

datetest.o: datetest.c date.h unittest.h
	gcc $(CFLAGS) -c datetest.c -o datetest.o

listtest.o: listtest.c list.h date.h unittest.h
	gcc $(CFLAGS) -c listtest.c -o listtest.o

heaptest.o: heaptest.c heap.h date.h unittest.h input.h devicepair.h
	gcc $(CFLAGS) -c heaptest.c -o heaptest.o

datetest.exe: datetest.o date.o
	gcc $(CFLAGS) datetest.o date.o -o datetest

listtest.exe: listtest.o date.o list.o
	gcc $(CFLAGS) listtest.o date.o list.o -o listtest

heaptest.exe: heaptest.o date.o heap.o input.o
	gcc $(CFLAGS) heaptest.o date.o heap.o input.o devicepair.o -o heaptest



test: listtest.exe datetest.exe heaptest.exe

runtest: listtest.exe datetest.exe heaptest.exe
	./listtest.exe
	./datetest.exe
	./heaptest.exe

.DEFAULT_GOAL := all