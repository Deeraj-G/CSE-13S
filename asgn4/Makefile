CC = clang
CFLAGS = -Wall -Wpedantic -Werror -Wextra
LFLAGS = -lm

all: tsp


tsp: tsp.o graph.o path.o stack.o
	$(CC) $(CFLAGS) -o tsp tsp.o graph.o path.o stack.o $(LFLAGS)

graph.o: graph.c
	$(CC) $(CFLAGS) -c graph.c

path.o: path.c
	$(CC) $(CFLAGS) -c path.c

stack.o: stack.c
	$(CC) $(CFLAGS) -c stack.c

clean:
	rm -f tsp *.o

format:
	clang-format -i -style=file *.c *.h
