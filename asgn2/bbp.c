#include "mathlib.h"
#include <stdio.h>
static int k;

double pi_bbp(void) {
	double current = 1.0;
	double sum = 0.0;
	double exp = 16;
	for (k = 0; current >= EPSILON; k++) {
		current = (k * ((120 * k) + 151)) + 47;
		current = current / (k * (k * (k * ((512 * k) + 1024) + 712) + 194) + 15);
		
		if (k > 0) {
			current = current / exp;
			exp = exp * 16;
		}
	
		sum += current;
	
	}
	return sum;


}

int pi_bbp_terms(void) {
	return k;




}
