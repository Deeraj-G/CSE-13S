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


typedef enum { ALL, INSERTION, SHELL, HEAP, QUICK, HELP, NUM_SORTS } Sorts;
const char *names[] = { "shell sort", "insertion sort", "heap sort", "quick sort" };


int main(int argc, char **argv) {
	Stats stats;
	stats.moves = 0;
	stats.compares = 0;
	uint32_t seed = 13371453;	
	uint32_t elements = 100;
	uint32_t mask = 0x3FFFFFFF;

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
                        s = insert_set(ALL, s);
                        break;
		case 'i':
			reset(&stats);
			s = insert_set(INSERTION, s);
			insertion_sort(&stats, A, elements);
			break;
		case 's':
			reset(&stats);
                        s = insert_set(SHELL, s);
			shell_sort(&stats, A, elements);
                        break;
		case 'e':
			reset(&stats);
                        s = insert_set(HEAP, s);
			heap_sort(&stats, A, elements);
                        break;
		case 'q':
			reset(&stats);
			s = insert_set(QUICK, s);
			quick_sort(&stats, A, elements);
			break;
		case 'n':
			break;

		}
	}

	for (Sorts x = ALL; x < NUM_SORTS; x++) {
		if (member_set(x, s)) {
			
			if (x == INSERTION) {
				printf("Insertion Sort, ");
			}
			else if (x == SHELL) {
				printf("Shell Sort, ");
			}
			else if (x == HEAP) {
				printf("Heap Sort, ");
			}
			else if (x == QUICK) {
				printf("Quick Sort, ");
			}

			printf("%d elements, ", elements);
			printf("%" PRIu64 " moves, ", stats.moves);
			printf("%"  PRIu64 " compares\n", stats.compares);
			
			for (uint32_t i = 0; i < elements; i++) {
         		       printf("%13" PRIu32 "\t", A[i]);
         		       if ((i + 1) % 5 == 0) {
				       printf("\n");
                }
        }
		}
	}

	return 0;
		
}
