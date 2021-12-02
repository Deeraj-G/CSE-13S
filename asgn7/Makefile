CC = clang
CFLAGS = -Wall -Wextra -Werror -Wpedantic

all: banhammer

banhammer: node.o bv.o bf.o ht.o parser.o speck.o

banhammer.o: banhammer.c
	$(CC) $(CFLAGS) -c banhammer.c

node.o: node.c
	$(CC) $(CFLAGS) -c node.c

bv.o: bv.c
	$(CC) $(CFLAGS) -c bv.c

bf.o: bf.c
	$(CC) $(CFLAGS) -c bf.c

ht.o: ht.c
	$(CC) $(CFLAGS) -c ht.c

parser.o: parser.c
	$(CC) $(CFLAGS) -c parser.c

speck.o: speck.c
	$(CC) $(CFLAGS) -c speck.c

clean:
	rm -f banhammer *.o

format:
	clang-format -i -style=file *.c *.h
