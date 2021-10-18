#include "heap.c"
#include "heap.h"
#include "insert.c"
#include "insert.h"
#include "quick.c"
#include "quick.h"
#include "set.h"
#include "shell.c"
#include "shell.h"
#include "stats.c"
#include "stats.h"

#include <inttypes.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define OPTIONS "haeisqn:p:r:"

// Copied the general structure for this code from TA Eugene's section video

typedef enum { HELP, HEAP, SHELL, INSERTION, QUICK, NO_INPUT, NUM_SORTS } Sorts;
const char *names[] = { "Shell Sort", "Insertion Sort", "Heap Sort", "Quick Sort" };

int main(int argc, char **argv) {
    Stats stats;
    stats.moves = 0;
    stats.compares = 0;
    uint64_t seed = 13371453;
    uint32_t print_elements = 100;
    uint32_t actual_elements = 100;
    uint32_t mask = 0x3FFFFFFF;
    bool no_input = true;
    Set s = empty_set();

    int opt = 0;
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 'a':
            no_input = false;
            s = insert_set(HEAP, s);
            s = insert_set(SHELL, s);
            s = insert_set(INSERTION, s);
            s = insert_set(QUICK, s);
            break;
        case 'e':
            no_input = false;
            s = insert_set(HEAP, s);
            break;
        case 's':
            no_input = false;
            s = insert_set(SHELL, s);
            break;
        case 'i':
            no_input = false;
            s = insert_set(INSERTION, s);
            break;
        case 'q':
            no_input = false;
            s = insert_set(QUICK, s);
            break;
        case 'h':
            no_input = false;
            s = insert_set(HELP, s);
            break;
        case 'n':
            actual_elements = atoi(optarg);
            break;
        case 'p':
            print_elements = atoi(optarg);
            break;
        case 'r':
            seed = atoi(optarg);
            break;
        default: printf("Invalid input"); break;
        }
    }

    srandom(seed);

    uint32_t *A = (uint32_t *) calloc(actual_elements, sizeof(uint32_t));
    for (uint32_t i = 0; i < actual_elements; i++) {
        A[i] = random() & mask;
    }

    for (Sorts x = HELP; x < NUM_SORTS; x++) {
        if (member_set(x, s)) {
            if (x == HELP || x == NO_INPUT) {
                if (no_input == true) {
                    printf("Select at least one sort to perform.\n");
                }
                printf("SYNOPSIS\n");
                printf("   A collection of comparison-based sorting algorithms.\n\n");
                printf("USAGE\n");
                printf("   ./sorting [-haeisqn:p:r:] [-n length] [-p elements] [-r seed]\n\n");
                printf("OPTIONS\n");
                printf("   -h              display program help and usage.\n");
                printf("   -a              enable all sorts.\n");
                printf("   -e              enable Heap Sort.\n");
                printf("   -i              enable Insertion Sort.\n");
                printf("   -s              enable Shell Sort.\n");
                printf("   -q              enable Quick Sort.\n");
                printf("   -n length       specify number of array elements (default: 100).\n");
                printf("   -p elements     specify number of elements to print (default: 100).\n");
                printf("   -r seed         specify random seed (default: 13371453).\n");
                break;
            }

            if (x == INSERTION) {
                insertion_sort(&stats, A, actual_elements);
                printf("Insertion Sort, ");
            }
            if (x == SHELL) {
                shell_sort(&stats, A, actual_elements);
                printf("Shell Sort, ");
            }
            if (x == HEAP) {
                heap_sort(&stats, A, actual_elements);
                printf("Heap Sort, ");
            }
            if (x == QUICK) {
                quick_sort(&stats, A, actual_elements);
                printf("Quick Sort, ");
            }

            printf("%d elements, ", actual_elements);
            printf("%" PRIu64 " moves, ", stats.moves);
            printf("%" PRIu64 " compares\n", stats.compares);

            for (uint32_t i = 0; i < print_elements; i++) {
                printf("%13" PRIu32 "\t", A[i]);
                if ((i + 1) % 5 == 0) {
                    printf("\n");
                }
            }

            reset(&stats);
            srandom(seed);

            for (uint32_t i = 0; i < actual_elements; i++) {
                A[i] = random() & mask;
            }
        }
    }
    free(A);
    return 0;
}
