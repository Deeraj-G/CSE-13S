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

// Used the steps listed in the asgn6.pdf doc by Dr. Long for this program

// Print this by default or when -h is specified
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

    // Initialize the default file for pbfile, infile, and outfile
    char *pbname = "rsa.pub";
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
        case 'n': pbname = optarg; break;
        case 'v': verbose = true; break;
        case 'h': usage(argv[0]); return EXIT_SUCCESS;
        default: usage(argv[0]); return EXIT_FAILURE;
        }
    }

    // Open the pbfile
    FILE *pbfile = fopen(pbname, "r");
    if (pbfile == NULL) {
        printf("ERROR: Invalid Public File");
    }

    // Initialize the mpz's
    mpz_t m, n, e, s;
    mpz_inits(m, n, e, s, NULL);

    // Read the public key from the pbfile
    rsa_read_pub(n, e, s, getenv("USER"), pbfile);

    // Print out the encryption statistics if verbose is true
    if (verbose == true) {
        printf("user = %s\n", getenv("USER"));
        gmp_printf("s (%d bits) = %Zd\n", mpz_sizeinbase(s, 2), s);
        gmp_printf("n (%d bits) = %Zd\n", mpz_sizeinbase(n, 2), n);
        gmp_printf("e (%d bits) = %Zd\n", mpz_sizeinbase(e, 2), e);
    }

    // Set the username
    mpz_set_str(m, getenv("USER"), 62);

    // Make sure the message is the same as m
    rsa_verify(m, s, e, n);

    // Encrypt the file and store the contents in the outfile
    rsa_encrypt_file(infile, outfile, n, e);

    // Close the files
    fclose(infile);
    fclose(outfile);
    fclose(pbfile);

    // Clear the mpz's
    mpz_clears(m, n, e, s, NULL);
}
