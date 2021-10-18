#include "heap.h"
#include "insert.h"
#include "quick.h"
#include "set.h"
#include "shell.h"
#include "stats.h"

#include <inttypes.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define OPTIONS "haeisqn:p:r:"

// Copied the general structure for this code from TA Eugene's section video
// Got the idea to use atoi(optarg) from tutor Brian Mak

typedef enum { HELP, HEAP, SHELL, INSERTION, QUICK, NO_INPUT, NUM_SORTS } Sorts;

int main(int argc, char **argv) {

    // Calls the stats struct
    Stats stats;
    // Initialize the moces and compares to 0, set the seed, n, and print elements values to their default values
    stats.moves = 0;
    stats.compares = 0;
    uint64_t seed = 13371453;
    uint32_t print_elements = 100;
    uint32_t actual_elements = 100;
    // Create the bit mask
    uint32_t mask = 0x3FFFFFFF;
    bool no_input = true;
    // Initialze an empty set
    Set s = empty_set();

    // Use the switch cases to check the command line inputs
    int opt = 0;
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 'a':
            no_input = false;
            // If -a is specified, all tests will run
            s = insert_set(HEAP, s);
            s = insert_set(SHELL, s);
            s = insert_set(INSERTION, s);
            s = insert_set(QUICK, s);
            break;
        case 'e':
            no_input = false;
            // If -e is specified, heap sort will run
            s = insert_set(HEAP, s);
            break;
        case 's':
            no_input = false;
            // If -s is specified, shell sort will run
            s = insert_set(SHELL, s);
            break;
        case 'i':
            no_input = false;
            // If -i is specified, insertion sort will run
            s = insert_set(INSERTION, s);
            break;
        case 'q':
            no_input = false;
            // If -q is specified, quick sort will run
            s = insert_set(QUICK, s);
            break;
        case 'h':
            no_input = false;
            // If -h is specified, the help message will be printed
            s = insert_set(HELP, s);
            break;
            // Set the length of array A equal to the specified number in the command line
        case 'n':
            actual_elements = atoi(optarg);
            break;
            // Set the number of elements to be printed equal to the specified number in the command line
        case 'p':
            print_elements = atoi(optarg);
            break;
            // Set the seed equal to the specified number in the command line
        case 'r':
            seed = atoi(optarg);
            break;
            // Print an error message if everthing else doesn't work
        default: printf("Invalid input\n"); break;
        }
    }

    // Set the random seem
    srandom(seed);

    // Allocate the dynamic memory
    uint32_t *A = (uint32_t *) calloc(actual_elements, sizeof(uint32_t));
    for (uint32_t i = 0; i < actual_elements; i++) {
        A[i] = random() & mask;
    }

    // If nothing is entered print the help message
    if (no_input == true) {
        printf("Select at least one sort to perform.\n");
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
    }

    // Check the if the values as defined in the enum belong in set s, if so, run the applicable sorts
    for (Sorts x = HELP; x < NUM_SORTS; x++) {
        if (member_set(x, s)) {
            // Print the help message
            if (x == HELP) {
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

            // Run the insertion sort
            if (x == INSERTION) {
                insertion_sort(&stats, A, actual_elements);
                printf("Insertion Sort, ");
            }
            // Run the shell sort
            if (x == SHELL) {
                shell_sort(&stats, A, actual_elements);
                printf("Shell Sort, ");
            }
            // Run the heap sort
            if (x == HEAP) {
                heap_sort(&stats, A, actual_elements);
                printf("Heap Sort, ");
            }
            // Run the quick sort
            if (x == QUICK) {
                quick_sort(&stats, A, actual_elements);
                printf("Quick Sort, ");
            }

            // Print the results of each sort
            printf("%d elements, ", actual_elements);
            printf("%" PRIu64 " moves, ", stats.moves);
            printf("%" PRIu64 " compares\n", stats.compares);

            // Print the results in the proper format
            for (uint32_t i = 0; i < print_elements; i++) {
                printf("%13" PRIu32 "\t", A[i]);
                if ((i + 1) % 5 == 0) {
                    printf("\n");
                }
            }

            // Reset the stats after each sorting algorithm
            reset(&stats);
            // Reset the seed after each sorting algorithm
            srandom(seed);

            // Create the specified number of random elements and properly bit mask them
            for (uint32_t i = 0; i < actual_elements; i++) {
                A[i] = random() & mask;
            }
        }
    }
    free(A);
    return 0;
}
