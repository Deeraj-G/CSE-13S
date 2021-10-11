#include "mathlib.h"

#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define OPTIONS "aebmrvnsh"

int main(int argc, char **argv) {
    int opt = 0;
    int no_input = true;
    int h_flag = false;
    int a_flag = false;
    int e_flag = false;
    int m_flag = false;
    int r_flag = false;
    int b_flag = false;
    int v_flag = false;
    int n_flag = false;
    int s_flag = false;
    int s_true = false;

    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        no_input = false;
        switch (opt) {
        case 'h': h_flag = true; break;
        case 'a': a_flag = true; break;
        case 'e': e_flag = true; break;
        case 'b': b_flag = true; break;
        case 'm': m_flag = true; break;
        case 'r': r_flag = true; break;
        case 'v': v_flag = true; break;
        case 'n': n_flag = true; break;
        case 's':
            s_flag = true;
            if ((a_flag == false) && (e_flag == false) && (b_flag == false) && (m_flag == false)
                && (r_flag == false) && (v_flag == false) && (n_flag == false)
                && (h_flag == false)) {
                s_true = true;
            }
            break;
        default: printf("Error"); break;
        }
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
        a_flag = false;
        e_flag = false;
        b_flag = false;
        m_flag = false;
        r_flag = false;
        v_flag = false;
        n_flag = false;
        s_flag = false;
        s_true = false;
        return 0;
    }

    if (s_true) {
        s_flag = false;
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
        //return 0;
    }

    if (a_flag) {
        printf("e() = %16.15lf, M_E = %16.15lf, diff = %16.15lf\n", e(), M_E, absolute(e() - M_E));
        if (s_flag) {
            printf("e() terms = %d\n", e_terms());
        }
        printf("pi_euler() = %16.15lf, M_PI = %16.15lf, diff = %16.15lf\n", pi_euler(), M_PI,
            absolute(pi_euler() - M_PI));
        if (s_flag) {
            printf("pi_euler() terms = %d\n", pi_euler_terms());
        }
        printf("pi_bbp() = %16.15lf, M_PI = %16.15lf, diff = %16.15lf\n", pi_bbp(), M_PI,
            absolute(pi_bbp() - M_PI));
        if (s_flag) {
            printf("pi_bbp() terms = %d\n", pi_bbp_terms());
        }
        printf("pi_madhava() = %16.15lf, M_PI = %16.15lf, diff = %16.15lf\n", pi_madhava(), M_PI,
            absolute(pi_madhava() - M_PI));
        if (s_flag) {
            printf("pi_madhava() terms = %d\n", pi_madhava_terms());
        }
        printf("pi_viete() = %16.15lf, M_PI = %16.15lf, diff = %16.15lf\n", pi_viete(), M_PI,
            absolute(pi_viete() - M_PI));
        if (s_flag) {
            printf("pi_viete() terms = %d\n", pi_viete_factors());
        }
        for (double t = 0.0; t <= 10.0; t += 0.1) {
            printf("sqrt_newton(%f) =  %16.15f, sqrt(%f) = %16.15f, diff = %16.15lf\n", t,
                sqrt_newton(t), t, sqrt(t), absolute(sqrt_newton(t) - sqrt(t)));
            if (s_flag) {
                printf("sqrt_newton() terms = %d\n", sqrt_newton_iters());
            }
        }
    }

    if (e_flag && (a_flag == false)) {
        printf("e() = %16.15lf, M_E = %16.15lf, diff = %16.15lf\n", e(), M_E, absolute(e() - M_E));
        if (s_flag) {
            printf("e() terms = %d\n", e_terms());
        }
    }

    if (b_flag && (a_flag == false)) {
        printf("pi_bbp() = %16.15lf, M_PI = %16.15lf, diff = %16.15lf\n", pi_bbp(), M_PI,
            absolute(pi_bbp() - M_PI));
        if (s_flag) {
            printf("pi_bbp() terms = %d\n", pi_bbp_terms());
        }
    }

    if (m_flag && (a_flag == false)) {
        printf("pi_madhava() = %16.15lf, M_PI = %16.15lf, diff = %16.15lf\n", pi_madhava(), M_PI,
            absolute(pi_madhava() - M_PI));
        if (s_flag) {
            printf("pi_madhava() terms = %d\n", pi_madhava_terms());
        }
    }

    if (r_flag && (a_flag == false)) {
        printf("pi_euler() = %16.15lf, M_PI = %16.15lf, diff = %16.15lf\n", pi_euler(), M_PI,
            absolute(pi_euler() - M_PI));
        if (s_flag) {
            printf("pi_euler() terms = %d\n", pi_euler_terms());
        }
    }

    if (v_flag && (a_flag == false)) {
        printf("pi_viete() = %16.15lf, M_PI = %16.15lf, diff = %16.15lf\n", pi_viete(), M_PI,
            absolute(pi_viete() - M_PI));
        if (s_flag) {
            printf("pi_viete() terms = %d\n", pi_viete_factors());
        }
    }

    if (n_flag && (a_flag == false)) {
        for (double t = 0.0; t <= 10.0; t += 0.1) {
            printf("sqrt_newton(%f) =  %16.15f, sqrt(%f) = %16.15f, diff = %16.15lf\n", t,
                sqrt_newton(t), t, sqrt(t), absolute(sqrt_newton(t) - sqrt(t)));
            if (s_flag) {
                printf("sqrt_newton() terms = %d\n", sqrt_newton_iters());
            }
        }
    }

    //    return 0;
}
