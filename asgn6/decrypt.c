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
// Used the steps listed in the asgn6.pdf doc by Dr. Long for this program

// Print this by default or when -h is specified
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

    // Initialize the default file for pvfile, infile, and outfile
    char *pvname = "rsa.priv";
    FILE *infile = stdin;
    FILE *outfile = stdout;

    // Initialize the default values of the command line specifications
    int opt = 0;
    bool verbose = false;

    // Loop through the command line options
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

    // Open the pvfile
    FILE *pvfile = fopen(pvname, "r");
    if (pvfile == NULL) {
        printf("ERROR: Invalid Private File");
    }

    // Initialize the mpz's
    mpz_t n, d;
    mpz_inits(n, d, NULL);

    // Read the private key
    rsa_read_priv(n, d, pvfile);

    // Print out the decryption statistics if verbose is true
    if (verbose == true) {
        gmp_printf("n (%zu bits) = %Zd\n", mpz_sizeinbase(n, 2), n);
        gmp_printf("e (%zu bits) = %Zd\n", mpz_sizeinbase(d, 2), d);
    }

    // Decrypt the file and store the results in the outfile
    rsa_decrypt_file(infile, outfile, n, d);

    // Close the files
    fclose(infile);
    fclose(outfile);
    fclose(pvfile);

    // Clear the mpz's
    mpz_clears(n, d, NULL);
}
