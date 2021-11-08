#include "node.h"
#include "code.h"
#include "defines.h"
#include "huffman.h"
#include "pq.h"
#include "io.h"
#include "stack.h"
#include <inttypes.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "header.h"

#define OPTIONS "i:o:vh"

// Based the structure and setup of the command line options off of Dr. Long's tsp.c in asgn4
// Used code from TA Eric to populate the histogram, set the file permissions, and build the codes

void usage(char *exec) {
    fprintf(stderr,
        "SYNOPSIS\n"
        "  A Huffman encoder.\n"
        "  Compresses a file using the Huffman coding algorithm.\n"
        "\n"
        "USAGE\n"
        "  %s [-h] [-i infile] [-o outfile]\n"
        "\n"
        "OPTIONS\n"
        "  -h             Program usage and help.\n"
        "  -v             Print compression statistics.\n"
        "  -i infile      Input file to compress.\n"
        "  -o outfile     Output of compressed data.\n",
        exec);
}

int main(int argc, char **argv) {

    int opt = 0;
    int infile = STDIN_FILENO;
    int outfile = STDOUT_FILENO;
    bool statistics = false;

    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 'i':
            infile = open(optarg, O_RDONLY);
            if (infile == -1) {
                fprintf(stderr, "Error: failed to open infile.\n");
                return EXIT_FAILURE;
            }
            break;
        case 'o':
            // Got the idea to use O_TRUNC and O_CREAT from Elmer in Discord
            outfile = open(optarg, O_WRONLY | O_CREAT | O_TRUNC);
            if (outfile == -1) {
                fprintf(stderr, "Error: failed to open outfile.\n");
                return EXIT_FAILURE;
            }
            break;
        case 'v': statistics = true; break;
        case 'h': usage(argv[0]); return EXIT_SUCCESS;
        default: usage(argv[0]); return EXIT_FAILURE;
        }
    }

    // This portion is from TA Eric
    // Populate the histogram with the correct frequency for each symbol
    uint64_t hist[ALPHABET] = { 0 };
    uint32_t unique_syms = 0;
    uint8_t buffer[BLOCK] = { 0 };
    hist[0] += 1;
    hist[ALPHABET - 1] += 1;
    int bytes_read;

    while ((bytes_read = read_bytes(infile, buffer, BLOCK)) > 0) {
        for (int i = 0; i < bytes_read; i++) {
            if (hist[buffer[i]] == 0) {
                unique_syms += 1;
            }
            hist[buffer[i]] += 1;
        }
    }

    // This portion is from TA Eric
    // Set the permissions for the outfile
    struct stat header;
    fstat(infile, &header);
    fchmod(outfile, header.st_mode);
    Header h = { 0, 0, 0, 0 };
    h.magic = MAGIC;
    h.permissions = header.st_mode;
    h.tree_size = 3 * unique_syms - 1;
    h.file_size = header.st_size;
    write_bytes(outfile, (uint8_t *) &h, sizeof(h));

    // Build the tree
    Node *root = build_tree(hist);

    // Initialize the Code table
    Code table[ALPHABET] = { 0 };

    // Build the Code table
    build_codes(root, table);

    // Dump the tree
    dump_tree(outfile, root);

    // This portion is from TA Eric
    // Write the codes
    lseek(infile, 0, SEEK_SET);
    while ((bytes_read = read_bytes(infile, buffer, BLOCK)) > 0) {
        for (int i = 0; i < bytes_read; i++) {
            write_code(outfile, &table[buffer[i]]);
        }
    }

    flush_codes(outfile);

    // Print the compression statistics if true
    if (statistics == true) {
    }

    // Free the allocated memory and close the opened text files
    delete_tree(&root);
    close(infile);
    close(outfile);
}
