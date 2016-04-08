OBJECTS	:= public.o server.o 
SOURCES	:= public.c server.c 
HEADERS	:= public.h server.h protocol.h

server: $(OBJECTS)
	gcc -lm -Wall $(OBJECTS) -o server -lpthread
	rm *.o
public.o: ../public/public.c ../public/public.h ../public/protocol.h
	gcc -c ../public/public.c
server.o: server.c server.h ../public/protocol.h ../public/public.h
	gcc -c server.c

