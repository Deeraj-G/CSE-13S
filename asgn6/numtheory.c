#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <gmp.h>
#include "numtheory.h"
#include <inttypes.h>

// Got most of is_prime from TA Eric Hernandez's section

void gcd(mpz_t d, mpz_t a, mpz_t b) {
    
    while (b != 0) {

        // Initialize an mpz_t variable
        mpz_t t;
        mpz_init(t);

        // Set t to b
        mpz_set(t, b);

        // Set b to a mod b
        mpz_mod(b, a, b);

        // Set a to t
        mpz_set(a, t);
    }

    // Set d equal to a
    d = a;
}
/*
void mod_inverse(mpz_t i, mpz_t a, mpz_t n) {

}
*/
void pow_mod(mpz_t out, mpz_t base, mpz_t exponent, mpz_t modulus) {

    // Initialize a mpz_t of value 0
    mpz_t zero;
    mpz_init(zero);
    
    // Set v equal to 1
    mpz_t v;
    mpz_init(v);
    mpz_set_ui(v, 1);

    // Set p equal to the base
    mpz_t p;
    mpz_init(p);
    mpz_set(p, base);

    // While loop
    while (exponent > zero) {
        
        // Create a temporary variable to check if the exponent is odd
        mpz_t temp;
        mpz_init(temp);
        mpz_set(temp, exponent);

        // Check if temp is odd
        if (mpz_mod_ui(temp, temp, 2) == 1) {
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

    out = v;
}

// Got most of is_prime from TA Eric Hernandez's section
bool is_prime(mpz_t n, uint64_t iters) {

    // Bit shifting for the n-1 = (2^s)r
    // Initialize mpz's for the bit shifting
    mpz_t n_min_one, two, r;
    mpz_inits(n_min_one, two, r, NULL);

    // Put a comment here
    mpz_sub_ui(n_min_one, n, 1);
    mpz_set_str(two, "2", 10);

    mp_bitcnt_t s = 2;
    while (mpz_divisible_2exp_p(n_min_one, s)) {
        s++;
    }
    s--;

    mpz_tdiv_q_2exp(r, n_min_one, s);

    // Initialize mpz's for the for loop
    mpz_t a, upper_bound, y, j;
    mpz_inits(a, upper_bound, y, j);

    for (uint64_t i = 0; i < iters; i++) {
        
        mpz_sub_ui(upper_bound, n, 3);
        mpz_urandomm(a, state, upper_bound);
        mpz_add_ui(a, a, 2);
        pow_mod(y, a, r, n);

        if ((mpz_cmp_ui(y, 1) != 0) && mpz_cmp(n_min_one, y) != 0) {

            // Set j to 1
            mpz_set_ui(j, 1);

            // Set sdec equal to s-1
            mp_bitcnt_t sdec = s - 1;

            // Set ndec equal to n-1
            mp_bitcnt_t ndec = n - 1;

            while ((mpz_cmp(j, sdec) <= 0) && (mpz_cmp(y, ndec) != 0)) {

                // Set y equal to power_mod(y,2,n)
                pow_mod(y, y, two, n);

                if (mpz_cmp_ui(y, 1) == 0) {
                    return false;
                }
                mpz_add_ui(j, j, 1);
            }

            if (mpz_cmp(y, n-1) != 0) {
                return false;
            }
        }
    }
    return true;
}
/*
void make_prime(mpz_t p, uint64_t bits, uint64_t iters) {

}
*/
