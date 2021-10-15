#include "set.h"
#include "insert.h"
#include "insert.c"
#include "stats.h"
#include <inttypes.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

typedef enum { INSERTION, HEAP, NUM_SORTS } Sorts;
const char *names[] = { "insertion sort", "heap sort" };


int main(void) {
	Stats stats;
	stats.moves = 0;
	stats.compares = 0;
	uint32_t seed = 13371453;	
	
	srandom(seed);	

	uint32_t *A = (uint32_t *)calloc(100, sizeof(uint32_t));
	for (uint32_t i = 0; i < 100; i++) {
		A[i] = random(); // Do the bitmask here
	}

	insertion_sort(&stats, A, 100);

	printf("[");
	for (uint32_t i = 0; i < 100; i++) {
		printf("%" PRIu32, A[i]);
		if ( i + 1 != 5) {
			printf(", ");
		}
	}
	printf("]\n");
	
	printf("moves = %" PRIu64 "\n", stats.moves);
	printf("compares = %" PRIu64 "\n", stats.compares);
	
	reset(&stats);
	}




	//Stats stats;


	/*
	Set s = empty_set();

	
	int opt = 0;
	while ((opt = getopt(argc, argv, "hi")) != -1) {
		switch(opt) {
		case 'h':
			s = insert_set(HEAP, s);
			break;
		case 'i':
			s = insert_set(INSERTION, s);
			break;
		}
	}

	for (Sorts x = INSERTION; x < NUM_SORTS; x++) {
		if (member_set(x, s)) {
			printf("%s is part of the set\n", names[x]);
		}
	}

	return 0;
		



	int ins = insertion_sort();
	for (int j = 0; j < sizeof(A); j++) {
		printf("insert() = %d", ins);
	}
*/
