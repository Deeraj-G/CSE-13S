#include "mathlib.h"
#include <stdio.h>
static int g;

double pi_madhava(void) {
	double current = 1.0;
	double sum = 0.0;
	double exp = -3.0;
	for (g = 0; current > EPSILON; g++) {
		if (g > 0) {
			current = 1.0;
			current = current / exp;
			exp = exp * -3.0;
		}
		current = current / (2 * g) + 1;
		sum += current;
	}
	sum = sum * sqrt_newton(12);
	return sum;
}



int pi_madhava_terms(void) {
	return g;
}
