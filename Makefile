CC=gcc
CFLAGS=-Wall -pedantic  -g -lreadline
RM=rm -f


bin/ep1sh: ep1.o parser.o 
	$(CC) $(CFLAGS) $^ -o $@

parser.o: parser.c
	$(CC) $(CFLAGS) -c $^

clean:
	$(RM) *.o *.gch
