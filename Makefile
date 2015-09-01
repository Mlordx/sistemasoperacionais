CC=gcc
CFLAGS=-Wall -pedantic -g -lreadline
RM=rm -f


bin/ep1sh: ep1.o shell.o parser.o
	$(CC) $(CFLAGS) $^ -o $@

shell.o: shell.c
	$(CC) $(CFLAGS) -c $^

parser.o: parser.c
	$(CC) $(CFLAGS) -c $^

clean:
	$(RM) *.o *.gch
