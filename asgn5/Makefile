CC = clang
CFLAGS = -Wall -Wpedantic -Werror -Wextra
LFLAGS = -lm

all: sorting


sorting: sorting.o insert.o shell.o heap.o quick.o stats.o
	$(CC) $(CFLAGS) -o sorting sorting.o insert.o shell.o heap.o quick.o stats.o $(LFLAGS)
insert.o: insert.c
	$(CC) $(CFLAGS) -c insert.c

shell.o: shell.c
	$(CC) $(CFLAGS) -c shell.c

heap.o: heap.c
	$(CC) $(CFLAGS) -c heap.c

quick.o: quick.c
	$(CC) $(CFLAGS) -c quick.c

stats.o: stats.c
	$(CC) $(CFLAGS) -c stats.c

clean:
	rm -f sorting *.o

format:
	clang-format -i -style=file *.c *.h
