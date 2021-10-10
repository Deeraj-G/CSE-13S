CC = clang
CFLAGS = -Wall -Wpedantic -Werror -Wextra
LDFLAGS = -lm

all: mathlib-test

e_test: e.o
	$(CC) $(CFLAGS) $(LDFLAGS) e.o -o e_test

bbp_test: bbp.o
	$(CC) $(CFLAGS) $(LDFLAGS) bbp.o -o bbp_test

madhava_test: madhava.o
	$(CC) $(CFLAGS) $(LDFLAGS) madhava.o -o madhava_test

euler_test: euler.o
	$(CC) $(CFLAGS) $(LDFLAGS) euler.o -o euler_test

viete_test: viete.o
	$(CC) $(CFLAGS) $(LDFLAGS) viete.o -o viete_test

newton_test: newton.o
	$(CC) $(CFLAGS) $(LDFLAGS) newton.o -o newton_test

mathlib-test: mathlib-test.o e.o bbp.o madhava.o euler.o viete.o newton.o
	$(CC) $(CFLAGS) $(LDFLAGS) mathlib-test.o e.o bbp.o madhava.o euler.o viete.o newton.o -o mathlib-test



e.o: e.c mathlib.h
	$(CC) $(CFLAGS) -c e.c

clean:
	rm -f e e.o

format:
	clang-format -i -style=file *.[ch]
