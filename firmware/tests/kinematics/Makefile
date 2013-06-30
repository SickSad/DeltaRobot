CFLAGS=-Wall -g -lm
LDLIBS=-lm


test: kinematics test.o
	$(CC) kinematics.o test.o -o test $(LDLIBS)

kinematics:
	$(CC) -c ../../kinematics.c $(CFLAGS)

clean:
	rm -f *.o
	rm test

