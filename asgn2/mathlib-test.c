#include "mathlib.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include "e.c"
#include "newton.c"
#include "madhava.c"
#include "bbp.c"
#include "viete.c"
#include "euler.c"
#define OPTIONS "aebmrvnsh"

int main(int argc, char **argv) {
    int opt = 0;
    int no_input = true;
    int h_flag = false;
    int a_flag = false;
    int e_flag = false;
    int m_flag = false;
    int eul_flag = false;
    int b_flag = false;
    int v_flag = false;
    int n_flag = false;
    int s_flag = false;
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        no_input = false;
	switch (opt) {
	case 'h': 
		h_flag = true;
		break;
	case 'a': ;
		a_flag = true;
		break;
        case 'e': ;
		e_flag = true;
        	break;
	case 'b': ;
		b_flag = true;
		break;
	case 'm': ;
		m_flag = true;
		break;
	case 'r': ;
		eul_flag = true;
		break;
	case 'v': ;
		v_flag = true;
		break;
	case 'n': ;
		n_flag = true;
		break;
	case 's': ;
		int e_count;
		e_count = e_terms();
		int newt_terms;
		newt_terms = sqrt_newton_iters();
		int b_count;
		b_count = pi_bbp_terms();
		int eul_count;
		eul_count = pi_euler_terms();
		int v_count;
		v_count = pi_viete_factors();
		int m_count;
	        m_count	= pi_madhava_terms();
		printf("e() terms = %d, sqrt_newton() terms = %d, pi_bbp() terms = %d, pi_euler() terms = %d, pi_viete() terms = %d, pi_madhava() terms = %d\n", e_count, newt_terms, b_count, eul_count, v_count, m_count);
		break;
	default:
	    break;
        }

    if (h_flag || no_input) {
	printf("SYNOPSIS\n   A test harness for the small numerical library.\n\n");
	printf("USAGE\n   ./mathlib-test [-aebmrvnsh]\n\n");
	printf("OPTIONS\n  -a   Runs all tests.\n");
	printf("  -e   Runs e test.\n");
	printf("  -b   Runs BBP pi test.\n");
	printf("  -m   Runs Madhava pi test.\n");
	printf("  -r   Runs Euler pi test.\n");
	printf("  -v   Runs Viete pi test.\n");
	printf("  -n   Runs Newton square root tests.\n");
	printf("  -s   Print verbose statistics.\n");
	printf("  -h   Display program synopsis and usage.\n");
	return 0;
    }

    else if (a_flag) {
	printf("e() = %16.15lf, M_E = %16.15lf, diff = %16.15lf\n", e(), M_E, absolute(e() - M_E));
	if (s_flag) {
		printf("e() terms = %d\n", e_terms());
	}
	printf("pi_euler() = %16.15lf, M_PI = %16.15lf, diff = %16.15lf\n", pi_euler(), M_PI, absolute(pi_euler() - M_PI));
	printf("pi_bbp() = %16.15lf, M_PI = %16.15lf, diff = %16.15lf\n", pi_bbp(), M_PI, absolute(pi_bbp() - M_PI));
	printf("pi_madhava() = %16.15lf, M_PI = %16.15lf, diff = %16.15lf\n", pi_madhava(), M_PI, absolute(pi_madhava() - M_PI));
	printf("pi_viete() = %16.15lf, M_PI = %16.15lf, diff = %16.15lf\n", pi_viete(), M_PI, absolute(pi_viete - M_PI);
        
	for (double t = 0.0; t <= 10.0; t += 0.1) {
		printf("sqrt_newton(%f) =  %16.15f, sqrt(%f) = %16.15f, diff = %16.15lf\n", t, sqrt_newton(t), t, sqrt(t), absolute(newt_test - sqrt(t));
	}
    }

    else if (e_flag) {
	printf("e() = %16.15lf, M_E = %16.15lf, diff = %16.15lf\n", e(), M_E, absolute(e() - M_E));
    	if (s_flag) {
		printf("e() terms = %d\n", e_terms());
	}
    }

    else if (m_flag) {
        printf("pi_madhava() = %16.15lf, M_PI = %16.15lf, diff = %16.15lf\n", pi_madhava(), M_PI, absolute(pi_madhava() - M_PI));
    	if (s_flag) {
		printf("pi_madhava() terms = %d\n", pi_madhava_terms());
	}
    }

    else if (eul_flag) {
	printf("pi_euler() = %16.15lf, M_PI = %16.15lf, diff = %16.15lf\n", pi_euler(), M_PI, absolute(pi_euler() - M_PI));
    	if (s_flag) {
		printf("pi_euler() terms = %d", pi_euler_terms());
	}
    }

    else if (b_flag) {
    	printf("pi_bbp() = %16.15lf, M_PI = %16.15lf, diff = %16.15lf\n", pi_bbp(), M_PI, absolute(pi_bbp() - M_PI));
    }

    else if (v_flag) {
	printf("pi_viete() = %16.15lf, M_PI = %16.15lf, diff = %16.15lf\n", pi_viete(), M_PI, absolute(pi_viete - M_PI);
    }

    else if (n_flag) {
	for (double t = 0.0; t <= 10.0; t += 0.1) {
                printf("sqrt_newton(%f) =  %16.15f, sqrt(%f) = %16.15f, diff = %16.15lf\n", t, sqrt_newton(t), t, sqrt(t), absolute(newt_test - sqrt(t));
	}
    }

    else if (s_flag) {

    }

    return 0;
    }
}
