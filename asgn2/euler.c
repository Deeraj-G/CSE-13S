#include "mathlib.h"
#include <stdio.h>
#include <inttypes.h>
static int f;

double pi_euler(void) {
	double current = 1.0;
	double sum = 0.0;
	double temp;

	for (f = 1; current > EPSILON; f++) {
		temp = f * f;
		current = 1.0 / temp;
		sum += current;
	}

	sum *= 6;
	sum = sqrt_newton(sum);
	return sum;
}



int pi_euler_terms(void) {
	return f;
}
