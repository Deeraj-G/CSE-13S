#include <stdio.h>
#include <gmp.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <inttypes.h>
#include "numtheory.h"
#include "randstate.h"

// Used Dr. Long's explanation of each function to base my code off of

// Used TA Eric Hernandez's pseudocode for this funcion
void rsa_make_pub(mpz_t p, mpz_t q, mpz_t n, mpz_t e, uint64_t nbits, uint64_t iters) {

    mpz_t p_min_one, q_min_one, gcd_e_n;
    mpz_inits(p_min_one, q_min_one, gcd_e_n, NULL);

    uint64_t pbits = (random() % (nbits / 2)) + (nbits / 4);
    uint64_t qbits = nbits - pbits;

    make_prime(p, pbits + 1, iters);
    make_prime(q, qbits + 1, iters);

    mpz_sub_ui(p_min_one, p, 1);
    mpz_sub_ui(q_min_one, q, 1);
    mpz_mul(n, p_min_one, q_min_one);

    mp_bitcnt_t en = nbits;

    do {
        mpz_urandomb(e, state, en);
        gcd(gcd_e_n, e, n);
    } while (mpz_cmp_ui(gcd_e_n, 1));

    mpz_set(e, gcd_e_n);
    mpz_clears(p_min_one, q_min_one, gcd_e_n, NULL);
}

void rsa_write_pub(mpz_t n, mpz_t e, mpz_t s, char username[], FILE *pbfile) {

    // Print n to the pbfile using the mpz_t format specifier
    gmp_fprintf(pbfile, "%ZX\n", n);

    // Print e to the pbfile using the mpz_t format specifier
    gmp_fprintf(pbfile, "%ZX\n", e);

    // Print s to the pbfile using the mpz_t format specifier
    gmp_fprintf(pbfile, "%ZX\n", s);

    // Print username to the pbfile using the string format specifier
    gmp_fprintf(pbfile, "%s\n", username);
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

    // Initialize mpz's
    mpz_t p_min_one, q_min_one, n;
    mpz_inits(p_min_one, q_min_one, n, NULL);

    // Find the totient
    mpz_sub_ui(p_min_one, p, 1);
    mpz_sub_ui(q_min_one, q, 1);
    mpz_mul(n, p_min_one, q_min_one);

    // Set d equal to the mod inverse of e and the totient
    mod_inverse(d, e, n);

    // Clear the mpz's
    mpz_clears(p_min_one, q_min_one, n, NULL);
}

void rsa_write_priv(mpz_t n, mpz_t d, FILE *pvfile) {

    // Print n to the pvfile using the mpz_t format specifier
    gmp_fprintf(pvfile, "%ZX\n", n);

    // Print d to the pvfile using the mpz_t format specifier
    gmp_fprintf(pvfile, "%ZX\n", d);
}

void rsa_read_priv(mpz_t n, mpz_t d, FILE *pvfile) {

    // Scan n from the pvfile with the mpz_t format specifier
    gmp_fscanf(pvfile, "%ZX\n", n);

    // Scan d from the pvfile with the mpz_t format specifier
    gmp_fscanf(pvfile, "%ZX\n", d);
}

void rsa_encrypt(mpz_t c, mpz_t m, mpz_t e, mpz_t n) {
    // Find m^e mod n and store the result in c
    pow_mod(c, m, e, n);
}

// Used the provided pseudocode for this function from Elmer in Discord
uint32_t lg(mpz_t n) {

    uint32_t k = 0;
    mpz_abs(n, n);
    while (mpz_cmp(n, 0) > 0) {
        mpz_fdiv_q_ui(n, n, 2);
        k += 1;
    }
    return k;
}

// Used the steps from Dr. Long for this function
void rsa_encrypt_file(FILE *infile, FILE *outfile, mpz_t n, mpz_t e) {

    uint32_t k = (lg(n) - 1) / 8;
    uint8_t *array = (uint8_t *) calloc(k, sizeof(uint8_t));

    mpz_t m, c;
    mpz_inits(m, c, NULL);

    array[0] = 0xFF;

    uint32_t j;
    //fopen(infile, "w+");
    //fopen(outfile, "w+");

    // Make sure all bytes in the file have been read
    // If the return value != k-1, it means an error occurred or the EOF was reached
    while ((j = fread(array + 1, sizeof(uint8_t), k - 1, infile)) == k - 1) {

        // Convert the read bytes into an mpz_t m
        mpz_import(m, j, 1, sizeof(uint8_t), 1, 0, array);

        // Encrypt m
        rsa_encrypt(c, m, e, n);

        // Write the encrypted number c to the outfile
        gmp_fprintf(outfile, "%ZX\n", c);
    }

    //fclose(infile);
    //fclose(outfile);
    mpz_clears(m, c, NULL);
}

void rsa_decrypt(mpz_t m, mpz_t c, mpz_t d, mpz_t n) {
    // Find c^d mod n and store the result in m
    pow_mod(m, c, d, n);
}

// Used the steps from Dr. Long for this function
void rsa_decrypt_file(FILE *infile, FILE *outfile, mpz_t n, mpz_t d) {
    if (infile && outfile) {
        mpz_set(n, d);
    }
}

void rsa_sign(mpz_t s, mpz_t m, mpz_t d, mpz_t n) {
    pow_mod(s, m, d, n);
}
bool rsa_verify(mpz_t m, mpz_t s, mpz_t e, mpz_t n) {

    mpz_t t;
    mpz_init(t);

    pow_mod(t, s, e, n);
    if (mpz_cmp(t, m) == 0) {
        return true;
    } else {
        return false;
    }

    mpz_clear(t);
}
