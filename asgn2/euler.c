#include "mathlib.h"
#include <stdio.h>
static int f;

double pi_euler(void) {
	double current = 1.0;
	double sum = 0.0;
	double temp;

	for (f = 1; current > EPSILON; f++) {
		temp = f;
		temp *= f;
		current = 1.0 / temp;
		sum += current;
	}

	sum *= 6;
	sum = sqrt_newton(sum);
	return sum;
}

int pi_euler_terms(void) {
	//Started at f = 1,so I have to subtract total terms by 1
	return f-1;
}
