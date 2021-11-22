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

    // Initialize mpz's
    mpz_t p_min_one, q_min_one, gcd_e_n, one, product, t, rand;
    mpz_inits(p_min_one, q_min_one, gcd_e_n, one, product, t, rand, NULL);

    // Choose a randome number between the bounds for pbits
    uint64_t pbits = (random() % (nbits / 2)) + (nbits / 4);

    // Assign the rest of the bits to qbits
    uint64_t qbits = nbits - pbits;

    // Make p and q prime
    make_prime(p, pbits + 1, iters);
    make_prime(q, qbits + 1, iters);

    // Calculate n
    mpz_mul(product, p, q);
    mpz_set(n, product);

    mpz_set_ui(one, 1);

    // Calculate the totient
    mpz_sub_ui(p_min_one, p, 1);
    mpz_sub_ui(q_min_one, q, 1);
    mpz_mul(t, p_min_one, q_min_one);

    mp_bitcnt_t en = nbits;

    mpz_set(rand, e);

    // Find a number coprime with the totient
    do {
        mpz_urandomb(rand, state, en);
        gcd(gcd_e_n, rand, t);
    } while (mpz_cmp(gcd_e_n, one) > 0);

    mpz_set(e, rand);
    mpz_clears(p_min_one, q_min_one, gcd_e_n, one, product, t, rand, NULL);
}

void rsa_write_pub(mpz_t n, mpz_t e, mpz_t s, char username[], FILE *pbfile) {

    // Print n to the pbfile using the mpz_t format specifier
    gmp_fprintf(pbfile, "%Zx\n", n);

    // Print e to the pbfile using the mpz_t format specifier
    gmp_fprintf(pbfile, "%Zx\n", e);

    // Print s to the pbfile using the mpz_t format specifier
    gmp_fprintf(pbfile, "%Zx\n", s);

    // Print username to the pbfile using the string format specifier
    gmp_fprintf(pbfile, "%s\n", username);
}

void rsa_read_pub(mpz_t n, mpz_t e, mpz_t s, char username[], FILE *pbfile) {

    // Scan n from the pbfile with the mpz_t format specifier
    gmp_fscanf(pbfile, "%Zx\n", n);

    // Scan e from the pbfile with the mpz_t format specifier
    gmp_fscanf(pbfile, "%Zx\n", e);

    // Scan s from the pbfile with the mpz_t format specifier
    gmp_fscanf(pbfile, "%Zx\n", s);

    // Scan username from the pbfile with the string format specifier
    gmp_fscanf(pbfile, "%s\n", username);
}

void rsa_make_priv(mpz_t d, mpz_t e, mpz_t p, mpz_t q) {

    // Initialize mpz's
    mpz_t p_min_one, q_min_one, t;
    mpz_inits(p_min_one, q_min_one, t, NULL);

    // Find the totient
    mpz_sub_ui(p_min_one, p, 1);
    mpz_sub_ui(q_min_one, q, 1);
    mpz_mul(t, p_min_one, q_min_one);

    // Set d equal to the mod inverse of e and the totient
    mod_inverse(d, e, t);

    // Clear the mpz's
    mpz_clears(p_min_one, q_min_one, t, NULL);
}

void rsa_write_priv(mpz_t n, mpz_t d, FILE *pvfile) {

    // Print n to the pvfile using the mpz_t format specifier
    gmp_fprintf(pvfile, "%Zx\n", n);

    // Print d to the pvfile using the mpz_t format specifier
    gmp_fprintf(pvfile, "%Zx\n", d);
}

void rsa_read_priv(mpz_t n, mpz_t d, FILE *pvfile) {

    // Scan n from the pvfile with the mpz_t format specifier
    gmp_fscanf(pvfile, "%Zx\n", n);

    // Scan d from the pvfile with the mpz_t format specifier
    gmp_fscanf(pvfile, "%Zx\n", d);
}

void rsa_encrypt(mpz_t c, mpz_t m, mpz_t e, mpz_t n) {
    // Find m^e mod n and store the result in c
    pow_mod(c, m, e, n);
}

// Used the steps from Dr. Long for this function
// Got the idea of using feof(infile) from Miles on Discord and tutor Eric Hernandez
void rsa_encrypt_file(FILE *infile, FILE *outfile, mpz_t n, mpz_t e) {

    size_t k = (mpz_sizeinbase(n, 2) - 1) / 8;
    size_t j = 0;
    uint8_t *array = calloc(k, sizeof(uint8_t));

    mpz_t m, c;
    mpz_inits(m, c, NULL);

    array[0] = 0xFF;

    // Make sure all bytes in the file have been read
    // If the return value != k-1, it means an error occurred or the EOF was reached
    while (feof(infile) == 0) {

        // Set j equal to the number of bytes read
        j = fread(array + 1, sizeof(uint8_t), k - 1, infile);

        // Convert the read bytes into an mpz_t m
        mpz_import(m, j + 1, 1, sizeof(uint8_t), 1, 0, array);

        // Encrypt m and put the message in c
        rsa_encrypt(c, m, e, n);

        // Write the encrypted number c to the outfile
        gmp_fprintf(outfile, "%Zx\n", c);
    }

    mpz_clears(m, c, NULL);
    free(array);
}

void rsa_decrypt(mpz_t m, mpz_t c, mpz_t d, mpz_t n) {
    // Find c^d mod n and store the result in m
    pow_mod(m, c, d, n);
}

// Used the steps from Dr. Long for this function
// Got the parameters of mpz_export from tutor Eric Hernandex
// Got the idea of feof(infile) from Miles on Discord and tutor Eric Hernandez
void rsa_decrypt_file(FILE *infile, FILE *outfile, mpz_t n, mpz_t d) {

    size_t k = (mpz_sizeinbase(n, 2) - 1) / 8;
    uint8_t *array = calloc(k, sizeof(uint8_t));
    size_t j;

    mpz_t m, c;
    mpz_inits(m, c, NULL);

    // Make sure all bytes in the file have been read
    // If the return value != k-1, it means an error occurred or the EOF was reached
    while (feof(infile) == 0) {

        gmp_fscanf(infile, "%Zx\n", c);

        // c should return a valid value
        if (mpz_cmp_ui(c, 0) > 0) {

            // Decrypt c and put the message in m
            rsa_decrypt(m, c, d, n);

            // Convert the read bytes into an mpz_t m
            mpz_export(array, &j, 1, sizeof(uint8_t), 1, 0, m);

            fwrite(array + 1, sizeof(uint8_t), j - 1, outfile);
        }
    }

    mpz_clears(m, c, NULL);
    free(array);
}

void rsa_sign(mpz_t s, mpz_t m, mpz_t d, mpz_t n) {
    // Calculate the sign according to the formula
    pow_mod(s, m, d, n);
}
bool rsa_verify(mpz_t m, mpz_t s, mpz_t e, mpz_t n) {

    mpz_t t;
    mpz_init(t);

    // Calculate t according to the formula
    pow_mod(t, s, e, n);

    // Make sure t equals m
    if (mpz_cmp(t, m) == 0) {
        mpz_clear(t);
        return true;
    } else {
        mpz_clear(t);
        return false;
    }

    mpz_clear(t);
}
