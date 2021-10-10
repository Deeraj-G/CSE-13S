CC = clang
CFLAGS = -Wall -Wpedantic -Werror -Wextra
LDFLAGS = -lm

all: e mathlib-test newton

e: e.o
	$(CC) -o e e.o

e.o: e.c mathlib.h
	$(CC) $(CFLAGS) -c e.c

mathlib-test: mathlib-test.o
	$(CC) -o mathlib-test mathlib-test.o

mathlib-test.o: mathlib-test.c mathlib.h
	$(CC) $(CFLAGS) -c mathlib.c

newton: newton.o
	$(CC) -o newton newton.o

newton.o: newton.c mathlib.h
	$(CC) $(CFLAGS) -c newton.c

clean:
	rm -f e e.o

format:
	clang-format -i -style=file *.[ch]
