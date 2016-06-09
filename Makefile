sock : testsocket.o configure_port.o main.o
	gcc $? -lserialport -o $@

testsocket.o : testsocket.c 
	gcc -g -c -lserialport -Wall $? -o $@ 
configure_port.o : configure_port.c 
	gcc -g -c -lserialport -Wall $? -o $@ 
main.o : main.c
	gcc -g -c -lserialport -Wall $? -o $@ 

clean :
	rm -f testsocket.o configure_port.o sock

