#include "mathlib.h"
#include <stdio.h>
static int newt_count;

// Used this code from Darrell Long's Python code in asgn2.pdf doc
double sqrt_newton(double x) {
	double z = 0.0;
	double y = 1.0;
	newt_count = 0;
	while (absolute(y - z) > EPSILON) {
		z = y;
		y = 0.5 * (z + x / z);
		newt_count += 1;
	}
	return y;
    }

int sqrt_newton_iters() {
	return newt_count;
}
