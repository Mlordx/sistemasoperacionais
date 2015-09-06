CC=gcc
CFLAGS=-Wall -pedantic -g -lreadline -lpthread
RM=rm -f

bin/ep1: scheduler.o time_handler.o first_in_first_out.o ep1.o
	$(CC) $^ -o $@ $(CFLAGS)

scheduler.o: scheduler.c
	$(CC) $(CFLAGS) -c $^

time_handler.o: time_handler.c
	$(CC) $(CFLAGS) -c $^

first_in_first_out.o: first_in_first_out.c
	$(CC) $(CFLAGS) -c $^

bin/ep1sh: ep1sh.o shell.o parser_shell.o
	$(CC) $(CFLAGS) $^ -o $@

shell.o: shell.c
	$(CC) $(CFLAGS) -c $^

parser_shell.o: parser_shell.c
	$(CC) $(CFLAGS) -c $^

clean:
	$(RM) *.o *.gch