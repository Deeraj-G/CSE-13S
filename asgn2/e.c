#include "mathlib.h"
#include <stdio.h>
static int count;

// Computes euler's number and finds the number of terms that were computed
double e(void) {
    double factorial = 1.0;
    double n = 1.0;
    //I start with factorial = 1, so count must be initialized to 1
    count = 1;
    for (int i = 0; (1/factorial) > EPSILON; i++) {
        factorial = factorial * (i + 1);
        n = n + (1 / factorial);
        count += 1;
    }
    return n;
}

int e_terms(void) {
	return count;
}
