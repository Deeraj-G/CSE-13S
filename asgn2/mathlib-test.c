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
	case 'a': ;
		break;
        case 'e': ;
		double e_test;
		e_test = e();
		double e_diff;
		e_diff = absolute(e_test - M_E);
        	printf("e() = %16.15lf, M_E = %16.15lf, diff = %16.15lf\n", e_test, M_E, e_diff);
        	break;
	case 'b': ;
		break;
	case 'm': ;
		break;
	case 'r': ;
		break;
	case "v': ;
		break;
	case 'n': ;
		double n_diff = 0.0;
		double newt_test;
		double t = 0.0;
		for (t; t < 10.0; t = t + 0.1) {
			newt_test = sqrt_newton(t);
			n_diff = absolute(newt_test - sqrt(t));
			printf("sqrt_newton(%f) =  %16.15f, sqrt(%f) = %16.15f, diff = %16.15lf\n", newt_test, t, sqrt(t), t, n_diff);
		}
		break;
	case 's': ;
		int e_count;
		e_count = e_terms();
		int newt_terms;
		newt_terms = sqrt_newton_iters();
		printf("e terms: %d, newton terms: %d\n", e_count, newt_terms);
		break;
	case 'h': ;
		break;
	default:
	    break;
        }
    }
    return 0;
}
