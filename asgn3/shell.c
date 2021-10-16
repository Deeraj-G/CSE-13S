#include "insert.h"
#include <stdint.h>
#include "stats.h"
#include <inttypes.h>
#include <stdio.h>
#include <math.h>


int gaps (uint32_t n) {
        
        uint32_t gap_length = log(3 + 2 * n) / log(3);
       	uint32_t var; 
        for (uint32_t i = gap_length; i > 0; i -= 1) {
                if (i > 0) {
			var = ((pow(3, i) - 1) / 2);
                        return var;
                }
        }
}



void shell_sort(Stats *stats, uint32_t *A, uint32_t n) {

	uint32_t j;
	uint32_t temp;
	uint32_t func = gaps(n);

	for (int i = 0; i < n; i++) {
		for ( int l = func; l < n; l -= 1) {
			j = l;
			temp = A[l];
			while (j >= func  && temp < A[j - func]) {
				A[j] = A[j - func];
				move(stats, A[j]);
				j -= func;
			}
		A[j] = temp;
		move(stats, A[j]);

		}
	}
}
