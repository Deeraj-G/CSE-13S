CC = clang
CFLAGS = -Wall -Wextra -Werror -Wpedantic
LFLAGS = $(shell pkg-config --libs gmp)

all: encrypt

encrypt: encrypt.o keygen.o numtheory.o randstate.o rsa.o
	$(CC) $(CFLAGS) -o encrypt encrypt.o keygen.o numtheory.o randstate.o rsa.o $(LFLAGS)

encrypt.o: encrypt.c
	$(CC) $(CFLAGS) -c encrypt.c

keygen.o: keygen.c
	$(CC) $(CFLAGS) -c keygen.c

numtheory.o: numtheory.c
	$(CC) $(CFLAGS) -c numtheory.c

randstate.o: randstate.c
	$(CC) $(CFLAGS) -c randstate.c

rsa.o: rsa.c
	$(CC) $(CFLAGS) -c rsa.c

clean:
	rm -f encrypt decrypt *.o

format:
	clang-format -i -style=file *.c *.h
