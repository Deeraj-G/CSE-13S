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

#define OPTIONS "hvi:o:n:"

void usage(char *exec) {
    fprintf(stderr,
        "SYNOPSIS\n"
        "   Encrypts data using RSA encryption.\n"
        "   Encrypted data is decrypted by the decrypt program.\n"
        "\n"
        "USAGE\n"
        "   %s [-hv] [-i infile] [-o outfile] -n pubkey\n"
        "\n"
        "OPTIONS\n"
        "   -h              Display program help and usage.\n"
        "   -v              Display verbose program output.\n"
        "   -i infile       Input file of data to encrypt (default: stdin).\n"
        "   -o outfile      Output file for encrypted data (default: stdout).\n"
        "   -n pvfile       Private key file (default: rsa.pub).\n",
        exec);
}

int main(int argc, char **argv) {

    char *pbname = "rsa.pub";
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
        case 'n': pbname = optarg; break;
        case 'v': verbose = true; break;
        case 'h': usage(argv[0]); return EXIT_SUCCESS;
        default: usage(argv[0]); return EXIT_FAILURE;
        }
    }

    FILE *pbfile = fopen(pbname, "r");
    if (pbfile == NULL) {
        printf("ERROR: Invalid Public File");
    }

    mpz_t m, n, e, s;
    mpz_inits(m, n, e, s, NULL);

    rsa_read_pub(n, e, s, getenv("USER"), pbfile);

    if (verbose == true) {
        printf("user = %s\n", getenv("USER"));
        gmp_printf("s (%d bits) = %Zd\n", mpz_sizeinbase(s, 2), s);
        gmp_printf("n (%d bits) = %Zd\n", mpz_sizeinbase(n, 2), n);
        gmp_printf("e (%d bits) = %Zd\n", mpz_sizeinbase(e, 2), e);
    }

    mpz_set_str(m, getenv("USER"), 62);

    rsa_verify(m, s, e, n);

    rsa_encrypt_file(infile, outfile, n, e);

    fclose(infile);
    fclose(outfile);
    fclose(pbfile);

    mpz_clears(m, n, e, s, NULL);
}
