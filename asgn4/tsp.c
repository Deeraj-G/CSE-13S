
// Implemented TA Christian Ocon's examples to structure my main()
// Used TA Omar's code for input scanning
// Used code from TA Eugene's section to get the vertex and edge weight

#include <assert.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#define OPTIONS "hvui:o:"

#include "graph.h"
#include "path.h"
#include "stack.h"
#include "vertices.h"

static FILE *input = NULL;
// I didn't get to the output portion so I'm commenting the next line out
//static FILE *output = NULL;
static bool undirected = false;
static bool verbose = false;

// Read through the command line options and specify variables
// Also read through the input file and add specified vertices and edges into the graph
int main(int argc, char **argv) {
    char *cities[VERTICES];
    char *input_file = NULL;
    char *output_file = NULL;
    char *atm = NULL;
    uint32_t i;
    uint32_t j;
    uint32_t k;
    uint32_t vertices = 0;
    bool no_input = true;
    bool help = false;

    // Use the switch cases to check the command line options
    int opt = 0;
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 'h':
            no_input = false;
            help = true;
            break;
        case 'v':
            no_input = false;
            verbose = true;
            break;
        case 'u':
            no_input = false;
            undirected = true;
            break;
        case 'i':
            no_input = false;
            input_file = optarg;
            break;
        case 'o':
            no_input = false;
            output_file = optarg;
            break;
        }
    }

    // Print out the help message if there's no input
    if (no_input == true) {
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

    // Print out the help message if -h is specified
    if (help == true) {
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
    }

    // The next part of this code was adapted from TA Omar's section video
    // Goes through the input file and reads the given info into variables to create the graph and add the vertices
    input = fopen(input_file, "r");
    char buffer[1024];
    fgets(buffer, 1024, input);
    // Set the number of vertices to the first number in the input file
    vertices = atoi(buffer);
    Graph *G = graph_create(vertices, undirected);

    // Make sure the number of vertices is valid
    if (vertices <= VERTICES) {
        // Puts the locations into the cities[] array
        for (uint32_t i = 0; i < vertices; ++i) {
            fgets(buffer, 1024, input);
            char *atm = strdup(buffer);
            cities[i] = atm;
        }

        // Got this part from TA Eugene's section
        // Read the vertex and edge weight inputs and split them up to be added to the graph
        while ((fscanf(input, "%" SCNu32 "%" SCNu32 "%" SCNu32 "\n", &i, &j, &k)) != EOF) {
            graph_add_edge(G, i, j, k);
        }
        // Graph is created properly
        graph_print(G);
    }

    else {
        printf("ERROR TOO MANY VERTICES");
    }
    // Free the allocated memory of atm
    free(atm);
    atm = NULL;
}

/*
    void dfs(Graph * G, uint32_t v, Path * curr, Path * shortest, char *cities[], FILE *outfile, bool verbose) {
        
        uint32_t city = fgets(input_file, "%s", cities);

        if (city > VERTICES) {
            printf("Error, too many vertices");
        }

        

        path_push_vertex(curr, v, G);
        graph_mark_visited(G, v);

        for (uint32_t w = 0; graph_has_edge(G, v, w); w++) {
            if (graph_visited(G, v) == false) {

                calls += 1;
                dfs(G, w, curr, shortest, cities, outfile, verbose);
            }
        }
    }
    */
