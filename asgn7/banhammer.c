#include "node.h"
#include "bv.h"
#include "bf.h"
#include "bst.h"
#include "ht.h"
#include <math.h>

// Got the regex pattern from tutor Eric Hernandez
#define REG_PATTERN "[A-Za-z0-9_]+(('|-)[A-Za-z0-9_]+)*"
#define OPTIONS "ht:f:s"

// Print this by default or when -h is specified
void usage(char *exec) {
    fprintf(stderr,
            "SYNOPSIS\n"
            "  A word filtering program for the GPRSC.\n"
            "  Filters out and reports bad words parsed from stdin.\n"
            "\n"
            "USAGE\n"
            "  %s [-hs] [-t size] [-f size]\n"
            "\n"
            "OPTIONS\n"
            "  -h           Program usage and help.\n"
            "  -s           Print program statistics.\n"
            "  -t size      Specify hash table size (default: 2^16).\n"
            "  -f size      Specify Bloom filter size (default: 2^20).\n",
        exec);
}

int main(int argc, char **argv) {

    // Create default values for the command line specifications
    int opt = 0;
    bool stats = false;
    uint32_t htsize = pow(2, 16);
    uint32_t bfsize = pow(2, 20);

    // Loop through the command line options
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 't':
            htsize = atoi(optarg);
            break;
        case 'f':
            bfsize = atoi(optarg);
            break;
        case 's': stats = true; break;
        case 'h': usage(argv[0]); return EXIT_SUCCESS;
        default: usage(argv[0]); return EXIT_FAILURE;
        }
    }

    // Create a Hashtable and set its size to htsize
    HashTable ht = ht_create(htsize);

    // Create a Bloom Filter and set its size to bfsize
    BloomFilter bf = bf_create(bfsize);

    // Got the rest of this function from tutor Eric Hernandez

    if (bf_size(bf) <= 0) {
        printf("ERROR: Invalid BloomFilter size");
    }

    if (ht_size(ht) <= 0) {
        printf("ERROR: Invalid HashTable size");
    }

    char badspeak[1024];

    fopen(badfile, "r");

    while (fscanf(bad_file, "%s\n", badspeak) != EOF) {
        bf_insert(bf, badspeak);
        ht_insert(ht, badspeak, newspeak);
    }

    fclose(badfile);












}
