#include "mathlib.h"
#include <stdio.h>
static int f;

// Calculate euler's solution to approximate pi
double pi_euler(void) {
	// Store the current value of the formula for the iteration
	double current = 1.0;
	// Store the summation of the loop
	double sum = 0.0;
	// Variable to store k*k from euler's solution
	double temp;

	// Loop to calculate the 1/k^2 part of euler's solution
	for (f = 1; current > EPSILON; f++) {
		// Calculate k^2
		temp = f;
		temp *= f;
		// Set the current iteration value equal to 1/k^2
		current = 1.0 / temp;
		// Sum the values of every iterated current to find the approximation of pi
		sum += current;
	}
	
	// Multiply summation by 6 accoridng to the formula
	sum *= 6;
	// Square root the sum according to euler's solution
	sum = sqrt_newton(sum);
	return sum;
}

// Return the number of computed terms in pi_eluer()
int pi_euler_terms(void) {
	//Started at f = 1,so I have to subtract total terms by 1
	return f-1;
}
