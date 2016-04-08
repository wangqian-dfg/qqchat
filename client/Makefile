OBJECTS	:= public.o client.o interface.o
SOURCES	:= public.c client.c interface.c
HEADERS	:= public.h client.h interface.h protocol.h

client: $(OBJECTS)
	gcc -lm -Wall $(OBJECTS) -o client -lpthread
	rm *.o
public.o: ../public/public.c ../public/public.h ../public/protocol.h
	gcc -c ../public/public.c
interface.o: interface.c interface.h ../public/public.h ../public/protocol.h
	gcc -c interface.c
client.o: client.c client.h interface.h ../public/protocol.h ../public/public.h
	gcc -c client.c

