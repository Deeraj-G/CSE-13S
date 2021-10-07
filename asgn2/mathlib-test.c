#include "mathlib.h"
#include <math.h>
#include <stdio.h>
#include <unistd.h>
#include "e.c"
#include "newton.c"
#define OPTIONS "aebmrvnsh"

int main(int argc, char **argv) {
    int opt = 0;
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 'e': ;
		double e_test;
		e_test = e();
        	printf("e(): %16.15lf, M_E: %16.15lf\n", e_test, M_E);
        	break;
	case 'n': ;
		double n_diff = 0.0;
		double newt_test;
		double l = 0.0;
		newt_test = sqrt_newton(l);
		for (l; l < 10.0; l = l + 0.1) {
			n_diff = absolute(newt_test - sqrt(l));
			return n_diff;
			printf("sqrt(): %16.15f, Actual sqrt: %16.15f, diff: %16.15lf\n", newt_test, sqrt(25.0), n_diff);
		}
		break;
	case 's': ;
		int e_count;
		e_count = e_terms();
		int newt_terms;
		newt_terms = sqrt_newton_iters();
		printf("e terms: %d, newton terms: %d\n", e_count, newt_terms);
		break;
	default:
	    break;
        }
    }
    return 0;
}
