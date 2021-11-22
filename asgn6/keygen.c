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

#define OPTIONS "hvb:i:n:d:s:"

// Used pseudocode from tutor Eric Hernandez for this file
// Used the steps listed in the asgn6.pdf doc by Dr. Long for this program

void usage(char *exec) {
    fprintf(stderr,
        "SYNOPSIS\n"
        "   Generates an RSA public/private key pair.\n\n"
        "USAGE\n"
        "   %s [-hv] [-b bits] -n pbfile -d pvfile\n\n"
        "OPTIONS\n"
        "   -h              Display program help and usage.\n"
        "   -v              Display verbose program output.\n"
        "   -b bits         Minimum bits needed for public key n (default: 256).\n"
        "   -i confidence   Miller-Rabin iterations for testing primes (default: 50).\n"
        "   -n pbfile       Public key file (default: rsa.pub).\n"
        "   -d pvfile       Private key file (default: rsa.priv).\n"
        "   -s seed         Random seed for testing.\n",
        exec);
}

int main(int argc, char **argv) {

    char *pbname = "rsa.pub";
    char *pvname = "rsa.priv";

    int opt = 0;
    int seed = time(NULL);
    int iters = 50;
    int bits = 256;
    bool verbose = false;

    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 'b': bits = atoi(optarg); break;
        case 'i': iters = atoi(optarg); break;
        case 'n': pbname = optarg; break;
        case 'd': pvname = optarg; break;
        case 's': seed = atoi(optarg); break;
        case 'v': verbose = true; break;
        case 'h': usage(argv[0]); return EXIT_SUCCESS;
        default: usage(argv[0]); return EXIT_FAILURE;
        }
    }

    FILE *pbfile = fopen(pbname, "w");
    if (pbfile == NULL) {
        printf("ERROR: Invalid Public File");
    }

    FILE *pvfile = fopen(pvname, "w");
    if (pvfile == NULL) {
        printf("ERROR: Invalid Private File");
    }

    fchmod(fileno(pvfile), 0600);

    randstate_init(seed);

    mpz_t s, p, q, n, e, d;
    mpz_inits(s, p, q, n, e, d, NULL);

    rsa_make_pub(p, q, n, e, bits, iters);

    rsa_make_priv(d, e, p, q);

    mpz_set_str(s, getenv("USER"), 62);

    rsa_sign(s, s, d, n);

    rsa_write_pub(n, e, s, getenv("USER"), pbfile);

    rsa_write_priv(n, d, pvfile);

    if (verbose == true) {
        printf("user = %s\n", getenv("USER"));
        gmp_printf("s (%d bits) = %Zd\n", mpz_sizeinbase(s, 2), s);
        gmp_printf("p (%d bits) = %Zd\n", mpz_sizeinbase(p, 2), p);
        gmp_printf("q (%d bits) = %Zd\n", mpz_sizeinbase(q, 2), q);
        gmp_printf("n (%d bits) = %Zd\n", mpz_sizeinbase(n, 2), n);
        gmp_printf("e (%d bits) = %Zd\n", mpz_sizeinbase(e, 2), e);
        gmp_printf("d (%d bits) = %Zd\n", mpz_sizeinbase(d, 2), d);
    }

    fclose(pvfile);
    fclose(pbfile);

    randstate_clear();

    mpz_clears(s, p, q, n, e, d, NULL);
}
