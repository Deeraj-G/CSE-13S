#include "insert.h"
#include <stdint.h>
#include "stats.h"
#include <inttypes.h>
#include <stdio.h>

// Implement the quick sort algorithm
void insertion_sort(Stats *stats, uint32_t *A, uint32_t n) {
	uint32_t j;
	uint32_t temp;
	// We compare the current element to the previous element, so i must start at 1
	for (uint32_t i = 1; i < n; i++) {
		
		j = i;
		temp = A[i];
		move(stats, temp);

		// j must be > 0 because it would give an out of range error otherwise
		// If temp < A[j - 1] then the current element must be moved back in the array
		
		while ((j > 0) && (cmp(stats, temp, A[j - 1])) < 0) {

			// Set the current element equal to the larger value	
			A[j] = A[j - 1];
			move(stats, A[j]);

			// Check the next previous element
			j -= 1;
		
		}
		// Set the lower element equal to the smaller value
		A[j] = temp;
		move(stats, A[j]);
	}
}
