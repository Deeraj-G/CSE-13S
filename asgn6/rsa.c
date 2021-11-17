#include <stdio.h>
#include <gmp.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <inttypes.h>
#include "numtheory.h"
#include "randstate.h"

// Used Dr. Long's explanation of the steps for this function
// Also used TA Eric Hernandez's pseudocode for this funcion
void rsa_make_pub(mpz_t p, mpz_t q, mpz_t n, mpz_t e, uint64_t nbits, uint64_t iters) {

    mpz_t p_min_one, q_min_one, gcd_e_n;
    mpz_inits(p_min_one, q_min_one, gcd_e_n, NULL);

    uint64_t pbits = (random() % (nbits / 2)) + (nbits / 4);
    uint64_t qbits = nbits - pbits;

    make_prime(p, pbits, iters);
    make_prime(q, qbits, iters);

    mpz_sub_ui(p_min_one, p, 1);
    mpz_sub_ui(q_min_one, q, 1);
    mpz_mul(n, p_min_one, q_min_one);

    do {
        mpz_urandomb(e, state, nbits);
        gcd(gcd_e_n, e, n);
    } while (mpz_cmp_ui(gcd_e_n, 1));

    mpz_set(e, gcd_e_n);
    mpz_clears(p_min_one, q_min_one, gcd_e_n, NULL);
}

void rsa_write_pub(mpz_t n, mpz_t e, mpz_t s, char username[], FILE *pbfile) {

    // Print n to the pbfile using the mpz_t format specifier
    gmp_fprintf(pbfile, "%ZX", n);
    gmp_fprintf(pbfile, "\n");

    // Print e to the pbfile using the mpz_t format specifier
    gmp_fprintf(pbfile, "%ZX", e);
    gmp_fprintf(pbfile, "\n");

    // Print s to the pbfile using the mpz_t format specifier
    gmp_fprintf(pbfile, "%ZX", s);
    gmp_fprintf(pbfile, "\n");

    // Print username to pbfile with a string format specifier
    gmp_fprintf(pbfile, "%s", username);
    gmp_fprintf(pbfile, "\n");
}

void rsa_read_pub(mpz_t n, mpz_t e, mpz_t s, char username[], FILE *pbfile) {

    // Scan n from the pbfile with the mpz_t format specifier
    gmp_fscanf(pbfile, "%ZX\n", n);

    // Scan e from the pbfile with the mpz_t format specifier
    gmp_fscanf(pbfile, "%ZX\n", e);

    // Scan s from the pbfile with the mpz_t format specifier
    gmp_fscanf(pbfile, "%ZX\n", s);

    // Scan username from the pbfile with the string format specifier
    gmp_fscanf(pbfile, "%s\n", username);
}

void rsa_make_priv(mpz_t d, mpz_t e, mpz_t p, mpz_t q) {
    mpz_set(d, e);
    mpz_set(p, q);
}

void rsa_write_priv(mpz_t n, mpz_t d, FILE *pvfile) {

    // Print n to the pvfile using the mpz_t format specifier
    gmp_fprintf(pvfile, "%ZX", n);
    gmp_fprintf(pvfile, "\n");

    // Print d to the pvfile using the mpz_t format specifier
    gmp_fprintf(pvfile, "%ZX", d);
    gmp_fprintf(pvfile, "\n");
}

void rsa_read_priv(mpz_t n, mpz_t d, FILE *pvfile) {

    // Scan n from the pvfile with the mpz_t format specifier
    gmp_fscanf(pvfile, "%ZX\n", n);

    // Scan d from the pvfile with the mpz_t format specifier
    gmp_fscanf(pvfile, "%ZX\n", d);
}

void rsa_encrypt(mpz_t c, mpz_t m, mpz_t e, mpz_t n) {
    mpz_set(c, m);
    mpz_set(e, n);
}

void rsa_encrypt_file(FILE *infile, FILE *outfile, mpz_t n, mpz_t e) {
    if (infile && outfile) {
        mpz_set(n, e);
    }
}

void rsa_decrypt(mpz_t m, mpz_t c, mpz_t d, mpz_t n) {
    mpz_set(m, c);
    mpz_set(d, n);
}

void rsa_decrypt_file(FILE *infile, FILE *outfile, mpz_t n, mpz_t d) {
    if (infile && outfile) {
        mpz_set(n, d);
    }
}

void rsa_sign(mpz_t s, mpz_t m, mpz_t d, mpz_t n) {
    mpz_set(s, m);
    mpz_set(d, n);
}
bool rsa_verify(mpz_t m, mpz_t s, mpz_t e, mpz_t n) {
    mpz_set(m, s);
    mpz_set(e, n);
    return false;
}
