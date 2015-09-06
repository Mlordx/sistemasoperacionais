CC=gcc
CFLAGS=-Wall -pedantic -g -lreadline -lpthread
RM=rm -f

bin/ep1: scheduler.o ep1.o
	$(CC) $(CFLAGS) $^ -o $@

scheduler.o: scheduler.c
	$(CC) $(CFLAGS) -c $^

bin/ep1sh: ep1sh.o shell.o parser_shell.o
	$(CC) $(CFLAGS) $^ -o $@

shell.o: shell.c
	$(CC) $(CFLAGS) -c $^

parser_shell.o: parser_shell.c
	$(CC) $(CFLAGS) -c $^

clean:
	$(RM) *.o *.gch
