#include "mathlib.h"
#include <math.h>
#include <stdio.h>
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
		double bbp_test;
		bbp_test = pi_bbp();
	       	double b_diff;
		b_diff = absolute(bbp_test - M_PI);
		printf("pi_bbp() = %16.15lf, M_PI = %16.15lf, diff = %16.15lf\n", bbp_test, M_PI, b_diff);	
		break;
	case 'm': ;
		double m_test;
		m_test = pi_madhava();
		double m_diff;
		m_diff = absolute(m_test - M_PI);
		printf("pi_madhava() = %16.15lf, M_PI = %16.15lf, diff = %16.15lf\n", m_test, M_PI, m_diff);
		break;
	case 'r': ;
		double eul_test;
		eul_test = pi_euler();
		double eul_diff;
		eul_diff = absolute(eul_test - M_PI);
		printf("pi_euler() = %16.15lf, M_PI = %16.15lf, diff = %16.15lf\n", eul_test, M_PI, eul_diff);
		break;
	case 'v': ;
		double v_test;
		v_test = pi_viete();
		double v_diff;
		v_diff = absolute(v_test - M_PI);
		printf("pi_viete() = %16.15lf, M_PI = %16.15lf, diff = %16.15lf\n", v_test, M_PI, v_diff);
		break;
	case 'n': ;
		double n_diff = 0.0;
		double newt_test;
		for (double t = 0.0; t <= 10.0; t = t + 0.1) {
			newt_test = sqrt_newton(t);
			n_diff = absolute(newt_test - sqrt(t));
			printf("sqrt_newton(%f) =  %16.15f, sqrt(%f) = %16.15f, diff = %16.15lf\n", t, newt_test, t, sqrt(t), n_diff);
		}
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
	case 'h': ;
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
		break;
	default:
	    break;
        }
    }
    return 0;
}
