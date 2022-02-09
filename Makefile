#Variables

CFLAGS = -Wall -pedantic -g
OBJ = date.o list.o input.o coronablinker.o
TESTOBJ = datetest.o listtest.o
BIN = coronablinker.exe datetest.exe listtest.exe

#Opearting system dependent variables
ifeq ($(OS), Windows_NT)
RM = del
BIN = coronablinker.exe datetest.exe listtest.exe
else
RM = rm
BIN = coronablinker datetest listtest
endif
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

clean: 
	$(RM) $(OBJ) $(TESTOBJ) $(BIN)

all: coronablinker.exe listtest.exe datetest.exe

#Test targets

datetest.o: datetest.c date.h unittest.h
	gcc $(CFLAGS) -c datetest.c -o datetest.o

listtest.o: listtest.c list.h date.h unittest.h
	gcc $(CFLAGS) -c listtest.c -o listtest.o

datetest.exe: datetest.o date.o
	gcc $(CFLAGS) datetest.o date.o -o datetest

listtest.exe: listtest.o date.o list.o
	gcc $(CFLAGS) listtest.o date.o list.o -o listtest

test: listtest.exe datetest.exe

runtest: listtest.exe datetest.exe
	./listtest.exe
	./datetest.exe

.DEFAULT_GOAL := all