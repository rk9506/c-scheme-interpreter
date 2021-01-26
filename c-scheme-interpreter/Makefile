CC=gcc
CFLAGS=-I.
DEPS = eval.c parser.c syntax.c printer.c types.c env.c hash_table.c

%.o: %.c $(DEPS)
	$(CC) %.c $(DEPS) -c -o $@ $< $(CFLAGS)

repl: repl.c $(DEPS)
	$(CC) repl.c $(DEPS) -o repl.o $(CFLAGS)

tests: tests.c $(DEPS)
	$(CC) tests.c $(DEPS) -o tests.o $(CFLAGS)
