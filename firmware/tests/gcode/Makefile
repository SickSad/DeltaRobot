CFLAGS=-Wall -g -lm
LDLIBS=-lm


test: gcode test.o
	$(CC) gcode.o test.o -o test $(LDLIBS)

gcode:
	$(CC) -c ../../gcode.c $(CFLAGS)

clean:
	rm -f *.o
	rm test

