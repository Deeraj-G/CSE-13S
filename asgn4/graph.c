#include "graph.h"

#include "vertices.h"

#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// I used code made by Dr. Long in the asgn4.pdf
// I based my code off of the descriptions for the functions in asgn4.pdf by Dr. Long

struct Graph {
    uint32_t vertices;
    bool undirected;
    bool visited[VERTICES];
    uint32_t matrix[VERTICES][VERTICES];
};

Graph *graph_create(uint32_t vertices, bool undirected) {
    Graph *G = (Graph *) calloc(1, sizeof(Graph));
    G->vertices = vertices;
    G->undirected = undirected;
    return G;
}

void graph_delete(Graph **G) {
    free(*G);
    *G = NULL;
    return;
}

uint32_t graph_vertices(Graph *G) {
    return G->vertices;
}

bool graph_add_edge(Graph *G, uint32_t i, uint32_t j, uint32_t k) {

    if ((i >= 0 && i < G->vertices) && (j >= 0 && j < G->vertices)) {
        G->matrix[i][j] = k;
        if (G->undirected == true) {
            G->matrix[j][i] = k;
        }
        return true;
    } else {
        return false;
    }
}

bool graph_has_edge(Graph *G, uint32_t i, uint32_t j) {

    if ((i >= 0 && i < G->vertices) && (j >= 0 && j < G->vertices) && (G->matrix[i][j] > 0)) {
        return true;
    }

    else {
        return false;
    }
}

uint32_t graph_edge_weight(Graph *G, uint32_t i, uint32_t j) {

    if ((i >= 0 && i < G->vertices) && (j >= 0 && j < G->vertices) && (G->matrix[i][j] > 0)) {
        return G->matrix[i][j];
    }

    else {
        return 0;
    }
}

bool graph_visited(Graph *G, uint32_t v) {

    if (G->visited[v] == true) {
        return true;
    }

    else {
        return false;
    }
}

void graph_mark_visited(Graph *G, uint32_t v) {
    if (v >= 0 && v < G->vertices) {
        G->visited[v] = true;
    }
}

void graph_mark_unvisited(Graph *G, uint32_t v) {
    if (v >= 0 && v < G->vertices) {
        G->visited[v] = false;
    }
}

void graph_print(Graph *G) {
    uint32_t row;
    uint32_t column;
    for (row = 0; row < G->vertices; row++) {
        for (column = 0; column < G->vertices; column++) {
            printf("%d ", G->matrix[row][column]);
        }
        printf("\n");
    }
}
