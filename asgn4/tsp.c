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

//static uint32_t calls = 0;
static FILE *input = NULL;
static FILE *output = NULL;

// Implemented TA Christian Ocon's examples to structure my main()
// Used TA Omar's code for input scanning

int main(int argc, char **argv) {
    char *cities[VERTICES];
    char *input_file = NULL;
    char *output_file = NULL;
    static bool undirected = false;
    static bool verbose = false;
    bool no_input = true;
    bool help = false;
    uint32_t vertices = 0;
    char* atm = NULL;
    char* again = NULL;
//    char* one = NULL;
  //  char* two = NULL;
    //char* three = NULL;
    uint32_t one_cp = 0;
    uint32_t two_cp = 0;
    uint32_t three_cp = 0;
    Graph *G = graph_create(vertices, undirected); 

    // Use the switch cases to check the command line inputs
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

    input = stdin;
    output = stdout;

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
        input = fopen(input_file, "r");
        char buffer[1024];
        fgets(buffer, 1024, input);
        vertices = atoi(buffer);
        
        if (vertices <= VERTICES) {
            for (uint32_t i = 0; i < vertices; ++i) {
                fgets(buffer, 1024, input);
                char* atm = strdup(buffer);
                cities[i] = atm;
            }

            while (NULL != fgets(buffer, 1024, input)) {
                again = strdup(buffer);
                //char* token = strtok(again, " ");

                sscanf(again, "%d %d %d", &one_cp, &two_cp, &three_cp);

//                one = atoi(one_cp);
  //              two = atoi(two_cp);
    //            three = atoi(three_cp);
//                printf("%d", "%d", "%d", one, two, three);                
                //printf("%" PRIu32, one_cp);
                graph_add_edge(G, one_cp, two_cp, three_cp);
            }
        }
        
        else {
            printf("ERROR TOO MANY VERTICES");
        }
    free(atm);
    atm = NULL;
    free(again);
    again = NULL;
    }

        /*
    }
    void dfs(Graph * G, uint32_t v, Path * curr, Path * shortest, char *cities[], FILE *outfile, bool verbose) {
        input = fopen(input_file_name, "r");
        char buffer[1025];
        sscanf(buffer, 1024, input);
        vertices = atoi(buffer);
        printf("%" PRIu32, vertices);
        
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
    

    //int main() {}
