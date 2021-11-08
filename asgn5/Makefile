CC = clang
CFLAGS = -Wall -Wextra -Werror -Wpedantic

all: encode decode

encode: encode.o node.o pq.o code.o io.o stack.o huffman.o
	$(CC) $(CFLAGS) -o encode encode.o node.o pq.o code.o io.o stack.o huffman.o

decode: decode.o node.o pq.o code.o io.o stack.o huffman.o
	$(CC) $(CFLAGS) -o decode decode.o node.o pq.o code.o io.o stack.o huffman.o

encode.o: encode.c
	$(CC) $(CFLAGS) -c encode.c

decode.o: decode.c
	$(CC) $(CFLAGS) -c decode.c

stack.o: stack.c
	$(CC) $(CFLAGS) -c stack.c

code.o: code.c
	$(CC) $(CFLAGS) -c code.c

node.o: node.c
	$(CC) $(CFLAGS) -c node.c

io.o: io.c
	$(CC) $(CFLAGS) -c io.c

pq.o: pq.c
	$(CC) $(CFLAGS) -c pq.c

huffman.o: huffman.c
	$(CC) $(CFLAGS) -c huffman.c

clean:
	rm -f encode decode *.o

format:
	clang-format -i -style=file *.c *.h
