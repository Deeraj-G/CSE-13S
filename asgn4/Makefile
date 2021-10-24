CC = clang
CFLAGS = -Wall -Wpedantic -Werror -Wextra

all: tsp


tsp: tsp.o graph.o path.o stack.o
	$(CC) $(CFLAGS) -o tsp tsp.o graph.o path.o stack.o

graph.o: graph.c
	$(CC) $(CFLAGS) -c graph.c

stack.o: stack.c
	$(CC) $(CFLAGS) -c stack.c

path.o: path.c
	$(CC) $(CFLAGS) -c path.c

clean:
	rm -f tsp *.o

format:
	clang-format -i -style=file *.c *.h
