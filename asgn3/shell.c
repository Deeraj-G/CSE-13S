#include "insert.h"
#include <stdint.h>
#include "stats.h"
#include <inttypes.h>
#include <stdio.h>
#include <math.h>

void shell_sort(Stats *stats, uint32_t *A, uint32_t n) {

	uint32_t j;
	uint32_t temp;

	for (int i = 0; i < n; i++) {
		for ( int l = gap_length; l < n; l -= 1) {
			j = l;
			temp = A[l];
			while (j >= gap_length && temp < A[j - gap_length]) {
				A[j] = A[j - gap_length];
				move(stats, A[j]);
				j -= gap_length;
			}
		A[j] = temp;
		move(stats, A[j]);

		}
	}
}

void gaps (uint32_t n) {
	uint32_t gap_length = log(3 + 2 * n) / log(3);
	for (uint32_t i = gap_length; i > 0; i -= 1) {
		if (i > 0) {
			return ((pow(3, i) - 1) / 2) ;
		}
	}
}

