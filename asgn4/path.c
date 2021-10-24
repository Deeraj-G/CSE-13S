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

struct Path {
    Stack *vertices;
    uint32_t length;
};

Path *path_create(void) {
    Path *p = (Path *) calloc(1, sizeof(Path));
    p->vertices = stack_create(VERTICES);
    p->length = 0;
    return p;
}

void path_delete(Path **p) {
    if (*p && (*p)->vertices) {
        free((*p)->vertices);
        free(*p);
        *p = NULL;
    }
    return;
}

bool path_push_vertex(Path *p, uint32_t v, Graph *G) {

    uint32_t x = 0;

    if (stack_empty(p->vertices) == true) {
        if (stack_push(p->vertices, v) == true && graph_has_edge(G, x, v)) {
            p->length = p->length + graph_edge_weight(G, 0, v);
            return true;
        } else {
            return false;
        }
    }

    else if (stack_peek(p->vertices, &x) == true && graph_has_edge(G, x, v)) {
        stack_push(p->vertices, v);
        p->length = p->length + graph_edge_weight(G, x, v);
        return true;
    }

    return false;
}

bool path_pop_vertex(Path *p, uint32_t *v, Graph *G) {

    uint32_t x;
    uint32_t p_top;

    if (stack_empty(p->vertices) == true) {
        return false;
    }

    else {
        p_top = stack_size(p->vertices);

        if (stack_peek(p->vertices, &x) == true) {
            stack_pop(p->vertices, &x);
            *v = x;
            p->length = p->length - graph_edge_weight(G, p_top, x);
            return true;
        }
    }
    return false;
}

uint32_t path_vertices(Path *p) {
    return stack_size(p->vertices);
}

uint32_t path_length(Path *p) {
    return p->length;
}

void path_copy(Path *dst, Path *src) {
    stack_copy(dst->vertices, src->vertices);
    dst->length = src->length;
}

/*
void path_print(Path *p, FILE *outfile, char *cities[]) {
    for (uint32_t i = 0; i < p->vertices->top; i++) {
        fprintf(outfile, "%s", cities[p->vertices->items[i]]);
        if (i + 1 != p->vertices->top) {
            fprintf(outfile, " -> ");
        }
    }
    fprintf(outfile, "\n");    
}

*/
