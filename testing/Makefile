CC=gcc
CFLAGS=-c -Wall
LDFLAGS=-lserialport
EXE=mspTest

$(EXE) : msp.o configure_port.o main.o
	$(CC) $? $(LDFLAGS) -o $@
configure_port.o : ../configure_port.c 
	$(CC) -g $(CFLAGS) $? -o $@ 
main.o : main.c
	$(CC) -g $(CFLAGS) $? -o $@ 
msp.o : ../msp.c
	$(CC) -g $(CFLAGS) $? -o $@ 
clean :
	rm -f msp.o main.o configure_port.o $(EXE)

