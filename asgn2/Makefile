CC = clang
CFLAGS = -Wall -Wpedantic -Werror -Wextra

all: e

e: e.o
	$(CC) -o e e.o

e.o: e.c mathlib.h
	$(CC) $(CFLAGS) -c e.c

clean:
	rm -f e e.o

format:
	clang-format -i -style=file *.[ch]
