#include "heap.h"

#include "stats.h"

#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

// I used the python pseudocode from Dr. Long to write this code

// This function returns the greater child between the arguments first and last
uint32_t max_child(Stats *stats, uint32_t *A, uint32_t first, uint32_t last) {

    uint32_t left = 2 * first;
    uint32_t right = left + 1;

    // Checks if the right value is<= last and checks if the right value is greater than the left value
    if (right <= last && ((cmp(stats, A[right - 1], A[left - 1])) > 0)) {
        // If the conditions are met, return right
        return right;
    } else {
        return left;
    }
}

// This function fixes the heap so it obeys the constraints of a heap after the largest element has been removed
void fix_heap(Stats *stats, uint32_t *A, uint32_t first, uint32_t last) {

    bool found = false;
    uint32_t mother = first;
    // This variable is set equal to the greater value between mother and last
    uint32_t great = max_child(stats, A, mother, last);

    // This loop checks if the array elements at mother is less than great, and swaps the two elements if it is true
    while (mother <= (last / 2) && (found == false)) {
        // Check if the array value at mother is less than the array value at great
        if ((cmp(stats, A[mother - 1], A[great - 1])) < 0) {
            // Swap the elements of mother and great
            swap(stats, &A[mother - 1], &A[great - 1]);
            // Sets mother equal to great
            mother = great;
            // Recalculates great now that mother is equal to the previous value of great
            great = max_child(stats, A, mother, last);
        } else {
            found = true;
        }
    }
}

// This function orders the array elements so it obeys the constraints of a max heap
void build_heap(Stats *stats, uint32_t *A, uint32_t first, uint32_t last) {

    uint32_t father;
    // This loop goes through the first half of the array A and orders the elements
    for (father = (last / 2); father > first - 1; father -= 1) {
        // Fixes the heap
        fix_heap(stats, A, father, last);
    }
}

// This function calls the various functions defined in this file and runs the heap sort
void heap_sort(Stats *stats, uint32_t *A, uint32_t n) {

    // Define the arguments
    uint32_t first = 1;
    uint32_t last = n;
    uint32_t leaf;

    // Builds the heap using the values in array A
    build_heap(stats, A, first, last);

    // Goes through all values in array A and sorts them in order
    for (leaf = last; leaf > first; leaf -= 1) {
        swap(stats, &A[first - 1], &A[leaf - 1]);
        fix_heap(stats, A, first, leaf - 1);
    }
}
