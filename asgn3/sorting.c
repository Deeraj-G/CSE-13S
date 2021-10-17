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

// Copied the general structure for this code from TA Eugene's section video

typedef enum { ALL, HEAP, SHELL, INSERTION, QUICK, HELP, NUM_SORTS } Sorts;
const char *names[] = { "shell sort", "insertion sort", "heap sort", "quick sort" };


int main(int argc, char **argv) {
	Stats stats;
	stats.moves = 0;
	stats.compares = 0;
	uint32_t seed = 13371453;	
	uint32_t elements = 100;
	uint32_t mask = 0x3FFFFFFF;

	Set s = empty_set();
	srandom(seed);

	uint32_t *A = (uint32_t *)calloc(100, sizeof(uint32_t));
	for (uint32_t i = 0; i < elements; i++) {
		A[i] = random() & mask;
	}

	int opt = 0;
	while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
		switch(opt) {
		case 'a':
			reset(&stats);
			s = insert_set(ALL, s);
                        break;
		case 'e':
                        reset(&stats);
                        s = insert_set(HEAP, s);
                        break;
		case 's':
                        reset(&stats);
                        s = insert_set(SHELL, s);
                        break;
		case 'i':
			reset(&stats);
			s = insert_set(INSERTION, s);
			break;
		case 'q':
			reset(&stats);
			s = insert_set(QUICK, s);
			break;
		case 'h':
			printf("SYNOPSIS\n");
			printf("   A collection of comparison-based sorting algorithms.\n\n");
			printf("USAGE\n");
			printf("   ./sorting [-haeisqn:p:r:] [-n length] [-p elements] [-r seed]\n\n");
			printf("OPTIONS\n");
			printf("   -h              display program help and usage.\n");
			printf("   -a              enable all sorts.\n");
			printf("   -e              enable Heap Sort.\n");
			printf("   -i              enable Insertion Sort.\n");
			printf("   -s              enable Shell Sort.\n");
			printf("   -q              enable Quick Sort.\n");
			printf("   -n length       specify number of array elements (default: 100).\n");
			printf("   -p elements     specify number of elements to print (default: 100).\n");
			printf("   -r seed         specify random seed (default: 13371453).\n");
			break;
		case 'n':
			break;
		case 'p':
			break;
		case 'r':
			break;
		}
	}

	for (Sorts x = ALL; x < NUM_SORTS; x++) {
		if (member_set(x, s)) {
			
			if (x == INSERTION) {
				insertion_sort(&stats, A, elements);
				printf("Insertion Sort, ");
			}
			else if (x == SHELL) {
				shell_sort(&stats, A, elements);
				printf("Shell Sort, ");
			}
			else if (x == HEAP) {
				heap_sort(&stats, A, elements);
				printf("Heap Sort, ");
			}
			else if (x == QUICK) {
				quick_sort(&stats, A, elements);
				printf("Quick Sort, ");
			}

			printf("%d elements, ", elements);
                        printf("%" PRIu64 " moves, ", stats.moves);
                        printf("%" PRIu64 " compares\n", stats.compares);
			
			for (uint32_t i = 0; i < elements; i++) {
         		       printf("%13" PRIu32 "\t", A[i]);
         		       if ((i + 1) % 5 == 0) {
				       printf("\n");
			       }
        		}
			
			reset(&stats);
                        srandom(seed);
			
			for (uint32_t i = 0; i < elements; i++) {
                              A[i] = random() & mask;
                        }
		}
	}
	free(A);
	return 0;
		
}
