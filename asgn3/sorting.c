#include "set.h"
#include "insert.h"
#include "insert.c"
#include "stats.h"
#include <inttypes.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "shell.c"
#include "shell.h"
#include <math.h>
#include "quick.h"
#include "quick.c"
#include "heap.c"
#include "heap.h"
#define OPTIONS "haeisqnpr"


typedef enum { INSERTION, SHELL, HEAP, QUICK, NUM_SORTS } Sorts;
const char *names[] = { "shell sort", "insertion sort", "heap sort", "quick sort" };


int main(int argc, char **argv) {
	Stats stats;
	stats.moves = 0;
	stats.compares = 0;
	uint32_t seed = 13371453;	
	uint32_t elements = 100;
	uint32_t mask = 0xFFFFFFFE;

	srandom(seed);

	uint32_t *A = (uint32_t *)calloc(100, sizeof(uint32_t));
	for (uint32_t i = 0; i < elements; i++) {
		A[i] = random() & mask; // Do the bitmask here
	}
	
	Set s = empty_set();
	
	int opt = 0;
	while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
		switch(opt) {
		case 'a':
                        s = insert_set(INSERTION, s);
			s = insert_set(SHELL, s);
			s = insert_set(HEAP, s);
			s = insert_set(QUICK, s);
                        break;
		case 'i':
			s = insert_set(INSERTION, s);
			insertion_sort(&stats, A, elements);
			break;
		case 's':
                        s = insert_set(SHELL, s);
			shell_sort(&stats, A, elements);
                        break;
		case 'e':
                        s = insert_set(HEAP, s);
			heap_sort(&stats, A, elements);
                        break;
		case 'q':
			s = insert_set(QUICK, s);
			quick_sort(&stats, A, elements);
			break;
		case 'n':
			break;

		}
	}

	for (Sorts x = INSERTION; x < NUM_SORTS; x++) {
		if (member_set(x, s)) {
			printf("%s is part of the set\n", names[x]);
		}
	}

	return 0;
		
}
