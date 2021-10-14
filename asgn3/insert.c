#include "insert.h"
#include <stdint.h>
#include "stats.h"


void quick_sort(Stats *stats, uint32_t *A, uint32_t n) {
	int j;
	int temp;
	for (int i = 1; i < sizeof(A); i++) {
		j = i;
		temp = A[i];
		while ( j > 0 && temp < A[j - 1]) {
			A[j] = A[j - 1];
			j -= 1;
		}
		A[j] = temp;
	}
}
