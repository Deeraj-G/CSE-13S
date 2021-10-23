#include "path.h"
#include "stack.h"
#include "graph.h"
#include "vertices.h"

#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

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
        if (stack_push(p->vertices, v) == true) {
            p->length = p->length + graph_edge_weight(G, 0, v);
            return true;
        }
        else {
            return false;
        }
    }

    else {
        if (stack_peek(p->vertices, x) == true) {
            stack_push(p->vertices, v);
            p->length = p->length + graph_edge_weight(G, x, v);
            return true;
        }
        return false;
    }
}

bool path_pop_vertex(Path *p, uint32_t *v, Graph *G) {
    uint32_t x;
    uint32_t top;
    if (stack_empty(p->vertices) == true) {
        return false;
    }
    else {
        top = stack_size(p->vertices);


}

uint32_t path_vertices(Path *p) {
    return stack_size(p->vertices);
}

uint32_t path_length(Path *p) {
    return p->length;
}

void path_copy(Path *dst, Path *src) {

}

void path_print(Path *p, FILE *outfile, char *cities[]) {

}


