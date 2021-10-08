#include "mathlib.h"
#include <stdio.h>
static int k;

double pi_bbp(void) {
	double constant;
	double current = 1.0;
	double sum = 0.0;
	for (k = 0; current > EPSILON; k++) {
		constant = 16.0;
		current = (k * ((120 * k) + 151)) + 47;
		current = current / (k * (k * (k * ((512 * k) + 1024) + 712) + 194) + 15);
		/*
		if (k == 0) {
			constant = 1;
		}
		else {	
			constant *= k;
			constant = 1 / constant;
			printf("1/constant: %lf\n", constant);
		}
		*/
		//printf("current efwe: %lf, k: %d\n", constant, k);
		current = (1/16) * current;			
		printf("constant: %lf, current: %lf\n", constant, current);
		
		sum += current;
	}
	printf("Final: %lf\n", sum);	
	return sum;


}

int pi_bbp_terms(void) {
	return k;




}
