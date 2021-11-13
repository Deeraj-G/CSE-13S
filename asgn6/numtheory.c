#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <gmp.h>
#include "numtheory.h"

void gcd(mpz_t d, mpz_t a, mpz_t b) {
    
    while (b != 0) {

        // Set d equal to b
        mpz_add(d, 0, b);

        // Set b equal to a mod b
        mpz_mod(b, a, b);

        // Set a equal to d
        mpz_add(a, 0, t);
    }

    return a;
}

void mod_inverse(mpz_t i, mpz_t a, mpz_t n) {

}

void pow_mod(mpz_t out, mpz_t base, mpz_t exponent, mpz_t modulus) {

    // Set v equal to 1
    mpz_t v;
    mpz_init(v);
    mpz_add(v, 0, 1);

    // Set p equal to the base
    mpz_t p;
    mpz_init(p);
    mpz_add(p, 0, base);

    // While loop
    while (exponent > 0) {
        
        if (exponent % 2 == 1) {
            // Set v equal to (v*p) mod n
            mpz_mul(v, v, p);
            mpz_mod(v, v, n);
        }

        // Set p equal to (p*p) mod n
        mpz_mul(p, p, p);
        mpz_mod(p, p, n);
        
        // Set d equal to d / 2
        mpz_fdiv_q(d, d, 2);
    }

    return v;
}

bool is_prime(mpz_t n, uint64_t iters) {

}

void make_prime(mpz_t p, uint64_t bits, uint64_t iters) {

}
