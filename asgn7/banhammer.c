#include "node.h"
#include "bv.h"
#include "bf.h"
#include "bst.h"
#include "ht.h"
#include "parser.h"
#include "messages.h"
#include <math.h>
#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <stdlib.h>
#include <unistd.h>
#include <regex.h>
#include "speck.h"
#include "salts.h"
#include <ctype.h>

// Got the regex pattern from tutor Eric Hernandez
#define REG_PATTERN "[A-Za-z0-9_]+(('|-)[A-Za-z0-9_]+)*"
#define OPTIONS     "ht:f:s"

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
    char oldspeak[1024];
    char newspeak[1024];
    char badspeak[1024];
    char *word = NULL;

    // Got the idea to use left shifting from miles on Discord
    uint32_t htsize = 1 << 16;
    uint32_t bfsize = 1 << 20;

    // Open the badfile and oldfile
    FILE *badfile = fopen("badspeak.txt", "r");
    FILE *oldfile = fopen("newspwak.txt", "r");

    // Store the violations to print reg
    Node *mixedmsg = bst_create();
    Node *badmsg = bst_create();

    // Loop through the command line options
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 't': htsize = atoi(optarg); break;
        case 'f': bfsize = atoi(optarg); break;
        case 's': stats = true; break;
        case 'h': usage(argv[0]); return EXIT_SUCCESS;
        default: usage(argv[0]); return EXIT_FAILURE;
        }
    }

    // Create a Hashtable and set its size to htsize
    HashTable *ht = ht_create(htsize);

    // Create a Bloom Filter and set its size to bfsize
    BloomFilter *bf = bf_create(bfsize);

    // Got the rest of this function from tutor Eric Hernandez

    if (bf_size(bf) <= 0) {
        printf("ERROR: Invalid BloomFilter size");
    }

    if (ht_size(ht) <= 0) {
        printf("ERROR: Invalid HashTable size");
    }

    while (fscanf(badfile, "%s\n", badspeak) != EOF) {
        bf_insert(bf, badspeak);
        ht_insert(ht, badspeak, newspeak);
    }

    // Close the badfile
    fclose(badfile);

    while (fscanf(oldfile, "%s %s\n", oldspeak, newspeak) != EOF) {
        bf_insert(bf, oldspeak);
        ht_insert(ht, oldspeak, newspeak);
    }

    // Close the oldfile
    fclose(oldfile);

    regex_t reg;

    if (regcomp(&reg, REG_PATTERN, REG_EXTENDED)) {
        fprintf(stderr, "ERROR: Failed to compile regex\n");
        return EXIT_FAILURE;
    }

    while ((word = next_word(stdin, &reg)) != NULL) {
        // Make the word lowercase
        // Used the while (word[i]) from https://www.educative.io/edpresso/what-is-the-tolower-function-in-c
        int i = 0;
        while (word[i]) {
            word[i] = tolower(word[i]);
            i++;
        }
        if (bf_probe(bf, word) == true) {
            Node *n = ht_lookup(ht, word);
            if (n != NULL && n->newspeak != NULL) {
                mixedmsg = bst_insert(mixedmsg, n->oldspeak, n->newspeak);
            } else if (n != NULL && n->newspeak == NULL) {
                badmsg = bst_insert(mixedmsg, n->oldspeak, n->newspeak);
            }
        }
    }

    if (stats == true) {
        // Print stats
    }

    else {
        if (bst_size(mixedmsg) > 0 && bst_size(mixedmsg) == 0) {
            printf("%s", goodspeak_message);
            bst_print(mixedmsg);
        } else if ((bst_size(mixedmsg) > 0) && bst_size(badmsg) > 0) {
            printf("%s", mixspeak_message);
            bst_print(badmsg);
            bst_print(mixedmsg);
        } else if (bst_size(mixedmsg) == 0 && bst_size(badmsg) > 0) {
            printf("%s", badspeak_message);
            bst_print(badmsg);
        }
    }
}
