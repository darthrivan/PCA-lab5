CFLAGS = -O2 -fno-inline -g -static
CC=gcc

all: munge_vectors8.2 munge_vectors16.2 munge_vectors32.2 munge_vectors64.2

munge_vectors8.2: munge_vectors8.c clock.c
	$(CC) $(CFLAGS) -o munge_vectors8.2 munge_vectors8.c clock.c 

munge_vectors16.2: munge_vectors16.c clock.c
	$(CC) $(CFLAGS) -o munge_vectors16.2 munge_vectors16.c clock.c 

munge_vectors32.2: munge_vectors32.c clock.c
	$(CC) $(CFLAGS) -o munge_vectors32.2 munge_vectors32.c clock.c 

munge_vectors64.2: munge_vectors64.c clock.c
	$(CC) $(CFLAGS) -o munge_vectors64.2 munge_vectors64.c clock.c 

clean:
	rm -f *.o *~ munge_vectors8.2 munge_vectors16.2 munge_vectors32.2 munge_vectors64.2


