#include <stdio.h>
#include <gmp.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <unistd.h>
#include <sys/stat.h>
#include <inttypes.h>
#include <time.h>
#include <fcntl.h>
#include "numtheory.h"
#include "rsa.h"
#include "randstate.h"

#define OPTIONS "i:o:n:vh"

// Used pseudocode from tutor Eric Hernandez for this file

void usage(char *exec) {
    fprintf(stderr,
        "SYNOPSIS\n"
        "   Decrypts data using RSA decryption.\n"
        "   Encrypted data is encrypted by the encrypt program.\n"
        "\n"
        "USAGE\n"
        "   %s [-hv] [-i infile] [-o outfile] -n privkey\n"
        "\n"
        "OPTIONS\n"
        "   -h              Display program help and usage.\n"
        "   -v              Display verbose program output.\n"
        "   -i infile       Input file of data to decrypt (default: stdin).\n"
        "   -o outfile      Output file for decrypted data (default: stdout).\n"
        "   -n pvfile       Private key file (default: rsa.priv).\n",
        exec);
}

int main(int argc, char **argv) {

    char *pvname = "rsa.priv";
    FILE *infile = stdin;
    FILE *outfile = stdout;

    int opt = 0;
    bool verbose = false;

    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 'i':
            if ((infile = fopen(optarg, "r")) == NULL) {
                fprintf(stderr, "Error: failed to open infile.\n");
                return EXIT_FAILURE;
            }
            break;
        case 'o':
            if ((outfile = fopen(optarg, "w")) == NULL) {
                fprintf(stderr, "Error: failed to open outfile.\n");
                return EXIT_FAILURE;
            }
            break;
        case 'n': pvname = optarg; break;
        case 'v': verbose = true; break;
        case 'h': usage(argv[0]); return EXIT_SUCCESS;
        default: usage(argv[0]); return EXIT_FAILURE;
        }
    }

    FILE *pvfile = fopen(pvname, "r");
    if (pvfile == NULL) {
        printf("ERROR: Invalid Private File");
    }

    mpz_t n, d;
    mpz_inits(n, d, NULL);

    rsa_read_priv(n, d, pvfile);

    if (verbose == true) {
        gmp_printf("n (%zu bits) = %Zd\n", mpz_sizeinbase(n, 2), n);
        gmp_printf("e (%zu bits) = %Zd\n", mpz_sizeinbase(d, 2), d);
    }

    rsa_decrypt_file(infile, outfile, n, d);

    fclose(infile);
    fclose(outfile);
    fclose(pvfile);

    mpz_clears(n, d, NULL);
}
