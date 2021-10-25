#include <assert.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#define OPTIONS "hvui:o:"

#include "graph.c"
#include "graph.h"
#include "path.c"
#include "path.h"
#include "stack.c"
#include "stack.h"
#include "vertices.h"
/*
static uint32_t calls = 0;
static FILE *infile = NULL;
static FILE *outfile = NULL;
static bool undirected = false;
static bool verbose = false;
bool no_input = true;

// Implemented TA Christian Ocan's examples to structure my main()

int main(int argc, char **argv) {

    // Use the switch cases to check the command line inputs
    int opt = 0;
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 'h':
            no_input = false;
            printf("SYNOPSIS\n");
            printf("  Traveling Salesman Problem using DFS.\n\n");
            printf("USAGE\n");
            printf("  ./tsp [-u] [-v] [-h] [-i infile] [-o outfile]\n\n");
            printf("OPTIONS\n");
            printf("  -u             Use undirected graph.\n");
            printf("  -v             Enable verbose printing.\n");
            printf("  -h             Program usage and help.\n");
            printf("  -i infile      Input containing graph (default: stdin)\n");
            printf("  -o outfile     Output of computed path (default: stdout)\n");
            break;
        case 'v':
            no_input = false;
            verbose = true;
            break;
        case 'u':
            no_input = false;
            undirected = true;
            break;
        case 'i': no_input = false *infile = atoi(optarg); break;
        case 'o':
            no_input = false;
            *outfile = atoi(optarg);
            break;
        }
    }
}

if (no_input = false) {
    printf("SYNOPSIS\n");
    printf("  Traveling Salesman Problem using DFS.\n\n");
    printf("USAGE\n");
    printf("  ./tsp [-u] [-v] [-h] [-i infile] [-o outfile]\n\n");
    printf("OPTIONS\n");
    printf("  -u             Use undirected graph.\n");
    printf("  -v             Enable verbose printing.\n");
    printf("  -h             Program usage and help.\n");
    printf("  -i infile      Input containing graph (default: stdin)\n");
    printf("  -o outfile     Output of computed path (default: stdout)\n");
}

void dfs(
    Graph *G, uint32_t v, Path *curr, Path *shortest, char *cities[], FILE *outfile, bool verbose) {

    if (no_input == false) {

        uint32_t city = fgets(infile, "%d", cities);

        if (city > VERTICES) {
            printf("Error, too many vertices");
        }

        fgets

            path_push_vertex(curr, v, G);
        graph_mark_visited(G, v);

        for (uint32_t w = 0; graph_has_edge(G, v, w); w++) {
            if (graph_visited(G, v) == false) {

                calls += 1;
                dfs(G, w, curr, shortest, cities, outfile, verbose);
            }
        }
    }
}
*/
int main() {
}
