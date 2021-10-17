#include "shell.h"

#include "stats.h"

#include <inttypes.h>
#include <math.h>
#include <stdint.h>
#include <stdio.h>

// I used the python pseudocode from Dr. Long to write this code

void shell_sort(Stats *stats, uint32_t *A, uint32_t n) {

    // Defining the maximum gap length that is possible
    uint32_t gap_max = log(3 + 2 * n) / log(3);
    // Initializing array of size gap_max
    uint32_t B[gap_max];
    // Variable to hold the gap length as it decreases by 1 every iteration
    uint32_t gap = gap_max;
    // Temporary variable to hold the nested loop iterator
    uint32_t j;
    // Temporary variable to hold the value of the array A at position r for the nested loop
    uint32_t temp;
    // Variable to hold the value of the current gap
    //uint32_t yield;

    // Loop to set the current value of the gap length
    for (uint32_t i = 0; i < gap_max; i += 1) {

        // Sets the current gap length equal to the formula defined in the python pseudocode
        B[i] = ((pow(3, gap) - 1) / 2);
        gap -= 1;
        // yield holds the current value of the gap
        //yield = B[i];

        // Loop to go through the array and switch the elements as applicable
        for (uint32_t r = B[i]; r >= B[i] && r < n; r++) {

            // Sets j equal to the iterator
            j = r;
            // Stores the current value of A[r] in temp
            temp = A[r];
            move(stats, A[r]);

            // Loop to switch the elements of the array if they fit the conditions
            while (j >= B[i] && (cmp(stats, temp, A[j - B[i]]) < 0)) {

                // Switches the gap separated values
                A[j] = A[j - B[i]];
                move(stats, A[j]);
                // Decrement j by the yield
                j -= B[i];
            }

            // Set the lower element of the array that was gap separated equal to the smaller value
            A[j] = temp;
            move(stats, A[j]);
        }
    }
}
