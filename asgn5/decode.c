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
    int infile;
    int outfile;
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

    Header h = { 0, 0, 0, 0 };
    read_bytes(infile, (uint8_t *) &h, sizeof(h));
    if (h.magic != MAGIC) {
        fprintf(stderr, "Error: Bad magic number");
        close(infile);
        close(outfile);
        exit(5);
    }
    fchmod(outfile, h.permissions);
}
