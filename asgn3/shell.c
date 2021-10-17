#include "shell.h"

#include "stats.h"

#include <inttypes.h>
#include <math.h>
#include <stdint.h>
#include <stdio.h>

// I used the python pseudocode from Dr. Long to write this code

void shell_sort(Stats *stats, uint32_t *A, uint32_t n) {

    uint32_t gap_max = log(3 + 2 * n) / log(3);
    uint32_t B[gap_max];
    uint32_t gap = gap_max;
    uint32_t j;
    uint32_t temp;

    // Loop to set the current value of the gap length
    for (uint32_t i = 0; i < gap_max; i += 1) {

        // Sets the current gap length equal to the formula defined in the python pseudocode
        B[i] = ((pow(3, gap) - 1) / 2);
        // Decrement the gap length for the next iteration
        gap -= 1;

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
                // Decrement j by the current value of array B
                j -= B[i];
            }

            // Set the lower element of the array that was gap separated equal to the smaller value
            A[j] = temp;
            move(stats, A[j]);
        }
    }
}
