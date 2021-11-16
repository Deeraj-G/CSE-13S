#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <gmp.h>
#include "numtheory.h"

void gcd(mpz_t d, mpz_t a, mpz_t b) {
    
    while (b != 0) {

        // Initialize an mpz_t variable
        mpz_t t;
        mpz_init(t);

        // Set t equal to b
        mpz_add(t, 0, b);

        // Set b equal to a mod b
        mpz_mod(b, a, b);

        // Set a equal to t
        mpz_add(a, 0, t);
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

    // Initialize a mpz_t of value 1
    mpz_t one;
    mpz_init(one);

    // Initialize an mpz_t of value 2
    mpz_t two;
    mpz_init(two);

    // Set v equal to 1
    mpz_t v;
    mpz_init(v);
    mpz_add(v, 0, one);

    // Set p equal to the base
    mpz_t p;
    mpz_init(p);
    mpz_add(p, 0, base);

    // While loop
    while (exponent > zero) {
        
        // Check if exponent is odd
        if (exponent % 2 == 1) {
            // Set v equal to (v*p) mod n
            mpz_mul(v, v, p);
            mpz_mod(v, v, modulus);
        }

        // Set p equal to (p*p) mod n
        mpz_mul(p, p, p);
        mpz_mod(p, p, modulus);

        // Set d equal to d / 2
        mpz_fdiv_q(exponent, exponent, two);
    }

    out = v;
}
/*
bool is_prime(mpz_t n, uint64_t iters) {

}

void make_prime(mpz_t p, uint64_t bits, uint64_t iters) {

}
*/
