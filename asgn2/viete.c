#include "mathlib.h"

#include <stdio.h>
static int d;

// Find an approximation of pi using Viète’s formula
double pi_viete(void) {
    // Store the current value of the summation's iteration
    double current = 0.0;
    // Store the value for the entire summation
    double product = 1.0;
    // Variable to hold the nested redicals
    double repeat = sqrt_newton(2);

    // Loop through the big product portion of Viète’s formula
    for (d = 1; current < 1 - EPSILON; d++) {
        // Divide the nested radicals by 2 according to the formula
        current = repeat / 2;
        // Store the current value into the summation total
        product *= current;
        // Store the current radical into the next iteration of the radical
        repeat = sqrt_newton(2 + repeat);
    }
    // Divide the product summation by 2 according to the formula
    product = 2 / product;
    return product;
}

// Return the number of computed terms in pi_viete()
int pi_viete_factors(void) {
    return d;
}
