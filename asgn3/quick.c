#include "quick.h"
#include "stats.h"
#include <stdint.h>
#include <inttypes.h>
#include <stdio.h>
#include <math.h>


uint32_t partition(Stats *stats, uint32_t *A,  uint32_t lo, uint32_t hi) {
	uint32_t i = lo - 1;
	uint32_t temp;
	uint32_t temp2 = A[i];

	for (uint32_t j = lo; j < hi; j++) {
		i += 1;
		temp = A[i - 1];

		A[i - 1] = A[j - 1];
		A[j - 1] = temp;
	}

	A[i] = A[hi - 1];
	A[hi - 1] = temp2;
	return i + 1;
}

void quick_sorter(Stats *stats, uint32_t *A,  uint32_t lo, uint32_t hi) {
	if (lo < hi) {
		uint32_t p = partition(A, lo, hi);
		quick_sorter(A, lo, p - 1);
		quick_sorter(A, p + 1, hi);
	}
}

void quick_sort(Stats *stats, uint32_t *A, uint32_t n) {
	quick_sorter(A, 1, n);


}
