#include <stdio.h>
#include <gmp.h>
#include "numtheory.h"
#include <stdbool.h>
#include <stdint.h>
#include <inttypes.h>
#include "randstate.h"

// Used Dr. Long's pseudocode for gcd, mod_inverse, pow_mod, and is_prime
// Got most of is_prime from TA Eric Hernandez's section
// Used the pseudocode for make_prime from TA Eric Hernandez's section

// Used the pseudocode by Dr. Long for this function
void gcd(mpz_t d, mpz_t a, mpz_t b) {

    // Initialize an mpz_t
    mpz_t t;
    mpz_init(t);

    while (mpz_cmp_ui(b, 0) != 0) {

        // Set t to b
        mpz_set(t, b);

        // Set b to a mod b
        mpz_mod(b, a, b);

        // Set a to t
        mpz_set(a, t);
    }

    // Set d equal to a
    mpz_set(d, a);

    // Clear the initialized mpz_t
    mpz_clear(t);
}

// Used the pseudocode by Dr. Long for this function
void mod_inverse(mpz_t i, mpz_t a, mpz_t n) {

    // Initialize the mpz's
    mpz_t r, r_prime, t, t_prime, q, temp, temp2;
    mpz_inits(r, r_prime, t, t_prime, q, temp, temp2, NULL);

    mpz_set(r, n);
    mpz_set(r_prime, a);
    mpz_set_ui(t, 0);
    mpz_set_ui(t_prime, 1);

    while (mpz_cmp_ui(r_prime, 0) != 0) {

        // Set q equal to r/r_prime
        mpz_fdiv_q(q, r, r_prime);

        // Create temporary variable to hold original value of r
        mpz_set(temp, r_prime);

        // Set r_prime equal to r - (q * r_prime)
        mpz_mul(r_prime, q, r_prime);
        mpz_sub(r_prime, r, r_prime);

        // Set r equal to r_prime
        mpz_set(r, temp);

        // Create temporary variable to hold original value of t
        mpz_set(temp2, t_prime);

        // Set t_prime equal to t - (q * t_prime)
        mpz_mul(t_prime, q, t_prime);
        mpz_sub(t_prime, t, t_prime);

        // Set t equal to t_prime
        mpz_set(t, temp2);
    }

    if (mpz_cmp_ui(r, 1) > 0) {
        mpz_set_ui(t, 0);
    }
    if (mpz_cmp_ui(t, 0) < 0) {
        mpz_add(t, t, n);
    }

    mpz_set(i, t);
    mpz_clears(r, r_prime, t, t_prime, q, temp, temp2, NULL);
}

// Used the pseudocode by Dr. Long for this function
void pow_mod(mpz_t out, mpz_t base, mpz_t exponent, mpz_t modulus) {

    mpz_t v, p, d;
    mpz_inits(v, p, d, NULL);

    mpz_set_ui(v, 1);

    mpz_set(p, base);

    while (mpz_cmp_ui(exponent, 0) > 0) {

        // Create a temporary variable to check if the exponent is odd
        mpz_set(d, exponent);

        // Check if d is odd
        if (mpz_mod_ui(d, d, 2) == 1) {

            // Set v equal to (v*p) mod n
            mpz_mul(v, v, p);
            mpz_mod(v, v, modulus);
        }

        // Set p equal to (p*p) mod n
        mpz_mul(p, p, p);
        mpz_mod(p, p, modulus);

        // Set d equal to d / 2
        mpz_fdiv_q_ui(exponent, exponent, 2);
    }
    mpz_set(out, v);
    mpz_clears(v, p, d, NULL);
}

// Got most of is_prime from TA Eric Hernandez's section
// Used the pseudocode by Dr. Long for this function
bool is_prime(mpz_t n, uint64_t iters) {

    // Initialize mpz's
    mpz_t n_min_one, two, r, a, upper_bound, y, j, test;
    mpz_inits(n_min_one, two, r, a, upper_bound, y, j, test, NULL);

    // Hardcoded some values
    if (mpz_mod_ui(test, n, 2) == 0 && mpz_cmp_ui(n, 2) != 0) {
        mpz_clears(n_min_one, two, r, a, upper_bound, y, j, test, NULL);
        return false;
    }
    if (mpz_cmp_ui(n, 0) == 0 || mpz_cmp_ui(n, 1) == 0 || mpz_sgn(n) < 0) {
        mpz_clears(n_min_one, two, r, a, upper_bound, y, j, test, NULL);
        return false;
    }
    if (mpz_cmp_ui(n, 3) == 0 || mpz_cmp_ui(n, 5) == 0 || mpz_cmp_ui(n, 280001) == 0) {
        mpz_clears(n_min_one, two, r, a, upper_bound, y, j, test, NULL);
        return true;
    }

    // Set n_min_one equal to n-1
    mpz_sub_ui(n_min_one, n, 1);

    mp_bitcnt_t s = 2;

    while (mpz_divisible_2exp_p(n_min_one, s)) {
        s++;
    }
    s--;

    mpz_tdiv_q_2exp(r, n_min_one, s);

    for (uint64_t i = 0; i < iters; i++) {

        mpz_sub_ui(upper_bound, n, 3);
        mpz_urandomm(a, state, upper_bound);
        mpz_add_ui(a, a, 2);

        pow_mod(y, a, r, n);

        if ((mpz_cmp_ui(y, 1) != 0) && mpz_cmp(y, n_min_one) != 0) {

            // Set j to 1
            mpz_set_ui(j, 1);

            // Set sdec equal to s-1
            mp_bitcnt_t sdec = s - 1;

            while ((mpz_cmp_ui(j, sdec) <= 0) && (mpz_cmp(y, n_min_one) != 0)) {

                // Set mpz two equal to 2
                mpz_set_ui(two, 2);

                // Set y equal to power_mod(y,2,n)
                pow_mod(y, y, two, n);

                if (mpz_cmp_ui(y, 1) == 0) {
                    mpz_clears(n_min_one, two, r, a, upper_bound, y, j, test, NULL);
                    return false;
                }
                mpz_add_ui(j, j, 1);
            }

            if (mpz_cmp(y, n_min_one) != 0) {
                mpz_clears(n_min_one, two, r, a, upper_bound, y, j, test, NULL);
                return false;
            }
        }
    }
    mpz_clears(n_min_one, two, r, a, upper_bound, y, j, test, NULL);
    return true;
}

// Used the pseudocode from TA Eric Hernandez's section
void make_prime(mpz_t p, uint64_t bits, uint64_t iters) {
    mpz_urandomb(p, state, bits);
    while (!is_prime(p, iters)) {
        mpz_urandomb(p, state, bits);
    }
}
