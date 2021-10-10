#include "mathlib.h"

#include <stdio.h>
static int g;

// Find an approximation of pi using the Madhava series
double pi_madhava(void) {
    // Store the value of the current loop iteration
    double current = 1.0;
    // Store the summed total of all current values
    double sum = 0.0;
    // Variable to store the current value of the exponentiated term
    double exp = -3.0;

    // Loop to calculate the summation of the Madhava series
    for (g = 0; absolute(current) > EPSILON; g++) {
        if (g > 0) {
            //Reset the value of current to accurately represent 1/(-3)^k
            current = 1.0;
            // Divide the current value by the exponentiated term
            current /= exp;
            // Store the next value of the exponent for successive loops
            exp *= -3.0;
        }

        // Divide the numerator of the summation by the denominator
        current /= (2 * g) + 1;
        // Add the current total to the sum total
        sum += current;
    }

    //Multiply the sum by sqrt(12) according to the Madhava series
    sum *= sqrt_newton(12);
    return sum;
}

// Return the number of iterated terms in pi_madhava()
int pi_madhava_terms(void) {
    return g;
}
