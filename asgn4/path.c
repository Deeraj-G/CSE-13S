#include "path.h"

#include "graph.h"
#include "stack.h"
#include "vertices.h"

#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// I used code made by Dr. Long in the asgn4.pdf
// I based my code off of the descriptions for the functions in asgn4.pdf by Dr. Long

// Define the Path structure
struct Path {
    Stack *vertices;
    uint32_t length;
};

// Create a Path with an allocated memory of size Path
Path *path_create(void) {
    Path *p = (Path *) calloc(1, sizeof(Path));
    // Initialize vertices and length
    p->vertices = stack_create(VERTICES);
    p->length = 0;
    return p;
}

// Delete the path and free up the path's allocated memory
void path_delete(Path **p) {
    if (*p && (*p)->vertices) {
        free((*p)->vertices);
        free(*p);
        *p = NULL;
    }
    return;
}

// Push vertex onto the path's stack
bool path_push_vertex(Path *p, uint32_t v, Graph *G) {

    uint32_t x = 0;

    // Check if stack is empty
    if (stack_empty(p->vertices) == true) {
        // stack_push checks if stack is full, make sure the graph has an edge
        if (stack_push(p->vertices, v) == true && graph_has_edge(G, x, v)) {
            // Add the edge weight to the path length
            p->length = p->length + graph_edge_weight(G, 0, v);
            return true;
        } else {
            return false;
        }
    }

    // Checks if there is already a value in the stack
    else if (stack_peek(p->vertices, &x) == true && graph_has_edge(G, x, v)) {
        // Push the vertex to the vertices stack
        stack_push(p->vertices, v);
        // Add the edge weight to the path length
        p->length = p->length + graph_edge_weight(G, x, v);
        return true;
    }

    return false;
}

// Pop vertex from the path's stack
bool path_pop_vertex(Path *p, uint32_t *v, Graph *G) {

    uint32_t x;
    uint32_t p_top;

    // If the stack is empty, there's nothing to pop
    if (stack_empty(p->vertices) == true) {
        return false;
    }

    else {
        p_top = stack_size(p->vertices);

        // Check if the stack is empty
        if (stack_peek(p->vertices, &x) == true) {
            // Pop if there's a viable value
            stack_pop(p->vertices, &x);
            *v = x;
            // Remove the edge weight from the path length
            p->length = p->length - graph_edge_weight(G, p_top, x);
            return true;
        }
    }
    return false;
}

// Return the number of vertices
uint32_t path_vertices(Path *p) {
    return stack_size(p->vertices);
}

// Return the length of the path
uint32_t path_length(Path *p) {
    return p->length;
}

// Create a copy of the path
void path_copy(Path *dst, Path *src) {
    stack_copy(dst->vertices, src->vertices);
    dst->length = src->length;
}

// Print out the values of the path to the outfile
void path_print(Path *p, FILE *outfile, char *cities[]) {
    stack_print(p->vertices, outfile, cities);
}
