#include "mathlib.h"
#include <stdio.h>
static int f;

double pi_euler(void) {
	double current = 1.0;
	double sum = 0.0;
	int temp;
	for (f = 1; current >= EPSILON; f++) {
		temp = f * f;
		printf("temp: %d", temp);
		current = 1 / temp;
		sum += current;
		printf("loop sum: %lf\n", sum);
	}

	sum = sum * 6;
	printf("%lf\n", sum);
	sum = sqrt_newton(sum);
	printf("sqrted: %lf\n", sum);
	return sum;
}



int pi_euler_terms(void) {
	return f-1;
}
