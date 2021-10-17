#include "quick.h"

#include "stats.h"

#include <inttypes.h>
#include <math.h>
#include <stdint.h>
#include <stdio.h>

// I used the python pseudocode from Dr. Long to write this code

// This function goes through array A and swaps elements until they are in increasing order
uint32_t partition(Stats *stats, uint32_t *A, uint32_t lo, uint32_t hi) {

    uint32_t i = lo - 1;

    // Loop to increment from the lo value to the hi value and swap the elements if the conditions are met
    for (uint32_t j = lo; j < hi; j++) {
        // Checks if A[j - 1] is less than A[hi - 1] to keep swapping elements until they are in order
        if ((cmp(stats, A[j - 1], A[hi - 1])) < 0) {
            i += 1;
            swap(stats, &A[i - 1], &A[j - 1]);
        }
    }

    // Swaps the lo value with the hi value
    swap(stats, &A[i], &A[hi - 1]);
    return i + 1;
}

// Recursively goes through array A and partitions each sub-array into smaller sub-arrays that are in increasing order
void quick_sorter(Stats *stats, uint32_t *A, uint32_t lo, uint32_t hi) {

    if (lo < hi) {

        // This variable will be used in the recursive calls
        uint32_t p = partition(stats, A, lo, hi);
        // Recursively call quick_sorter() to split the smaller sub-arrays into increasing order
        quick_sorter(stats, A, lo, p - 1);
        // Recursively call quick_sorter() to split the larger sub-arrays into increasing order
        quick_sorter(stats, A, p + 1, hi);
    }
}

// Calls the function quick_sorter() with defined arguments
void quick_sort(Stats *stats, uint32_t *A, uint32_t n) {
    quick_sorter(stats, A, 1, n);
}
