#include "mathlib.h"
#include "e.c"
#include "newton.c"
#include <stdio.h>
#include <unistd.h>
#define OPTIONS "aebmrvnsh"
#include <math.h>

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
		double newt_test;
		newt_test = sqrt_newton(25.0);
		printf("sqrt(): %16.15f, Actual sqrt: %16.15f\n", newt_test, sqrt(25.0));
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
