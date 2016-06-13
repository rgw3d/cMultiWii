sock : msp.o configure_port.o main.o
	gcc $? -lserialport -o $@

configure_port.o : configure_port.c 
	gcc -g -c -lserialport -Wall $? -o $@ 
main.o : main.c
	gcc -g -c -lserialport -Wall $? -o $@ 
msp.o : msp.c
	gcc -g -c -lserialport -Wall $? -o $@ 

clean :
	rm -f msp.o main.o configure_port.o sock

