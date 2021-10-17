CC = clang
CFLAGS = -Wall -Wpedantic -Werror -Wextra
LDFLAGS = -lm

all: sorting

insert_test: insert.o
	$(CC) $(CFLAGS) $(LDFLAGS) insert.o -o insert_test

shell_test: shell.o
	$(CC) $(CFLAGS) $(LDFLAGS) shell.o -o shell_test

heap_test: heap.o
	$(CC) $(CFLAGS) $(LDFLAGS) heap.o -o heap_test

quick_test: quick.o
	$(CC) $(CFLAGS) $(LDFLAGS) quick.o -o quick_test

sorting_test: sorting.o insert.o shell.o heap.o quick.o
	$(CC) $(CFLAGS) $(LDFLAGS) sorting.o insert.o shell.o heap.o quick.o -o sorting_test



insert.o: insert.c stats.h
	$(CC) $(CFLAGS) -c insert.c

shell.o: shell.c stats.h
	$(CC) $(CFLAGS) -c shell.c

heap.o: heap.c stats.h
	$(CC) $(CFLAGS) -c heap.c

euler.o: quick.c stats.h
	$(CC) $(CFLAGS) -c quick.c

sorting.o: sorting.c stats.h
	$(CC) $(CFLAGS) -c sorting.c

clean:
	rm -f insert_test shell_test heap_test quick_test sorting_test *.o *.exe

format:
	clang-format -i -style=file *.c *.h
