#include "mathlib.h"
#include <stdio.h>
static int k;

// Calculate the bbp formula to approximate pi
double pi_bbp(void) {
	// Variable to store the current value of the summation
	double current = 1.0;
	// Variable to sum the variable current after each iteration of the loop
	double sum = 0.0;
	// Variable to store the exponent for each loop
	double exp = 16;

	// Loop to compute the bbp formula
	for (k = 0; current >= EPSILON; k++) {
		// Compute the numerator of the formula
		current = (k * ((120 * k) + 151)) + 47;
		// Divide the numerator by the denominator of the formula
		current = current / (k * (k * (k * ((512 * k) + 1024) + 712) + 194) + 15);
		
		// Divide current by the stored exponent
		if (k > 0) {
			current = current / exp;
			// Update the exponent for each successive iteration
			exp = exp * 16;
		}
		// Sum the value of the current iteration to the total sum
		sum += current;
	
	}
	return sum;
}

// Find the number of terms iterated in pi_bbp()
int pi_bbp_terms(void) {
	return k;
}
