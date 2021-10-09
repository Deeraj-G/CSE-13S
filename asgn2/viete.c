#include "mathlib.h"
#include <stdio.h>
static int d;

double pi_viete(void) {
	double current = 3.0;
	double product = 1.0;
	double repeat = sqrt_newton(2);

	for (d = 1; current > 1 - current; d++) {
		current = repeat / 2;
		product *= current;
		repeat = sqrt_newton(2 + repeat);
		printf("repeat: %lf, current: %lf, product: %lf\n", repeat, current, product);
	}
	printf("%lf\n", product);	
	product = 2 / product;
	return product;
}

int pi_viete_factors(void) {
	return d;
}
