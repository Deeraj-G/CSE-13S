#include "mathlib.h"

#include <stdio.h>
static int i;

// Computes euler's number
double e(void) {
    // Variable to store the factorial k for each iteration
    double factorial = 1.0;
    // Variable to store the summation for each iteration of the loop
    double n = 1.0;

    // I start with factorial = 1.0, so i must be initialized to 1
    for (i = 1; (1 / factorial) > EPSILON; i++) {
        factorial *= i;
        n += (1 / factorial);
    }
    return n;
}

// Finds the number of terms that were computed in e()
int e_terms(void) {
    return i;
}
