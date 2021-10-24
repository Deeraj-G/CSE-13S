#include "graph.h"

#include "vertices.h"

#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// I used code made by Dr. Long in the asgn4.pdf
// I based my code off of the descriptions for the functions in asgn4.pdf by Dr. Long

// Defining the graph structure
struct Graph {
    uint32_t vertices;
    bool undirected;
    bool visited[VERTICES];
    uint32_t matrix[VERTICES][VERTICES];
};

// Allocate memory to a new Graph, initialize vertices and undirected to equal the arguments
Graph *graph_create(uint32_t vertices, bool undirected) {
    Graph *G = (Graph *) calloc(1, sizeof(Graph));
    G->vertices = vertices;
    G->undirected = undirected;
    return G;
}

// Delete graph and free up allocated memory
void graph_delete(Graph **G) {
    free(*G);
    *G = NULL;
    return;
}

// Return number of vertices in the graph
uint32_t graph_vertices(Graph *G) {
    return G->vertices;
}

// Add edge to graph
bool graph_add_edge(Graph *G, uint32_t i, uint32_t j, uint32_t k) {

    // Make sure the vertices are within bounds
    if ((i >= 0 && i < G->vertices) && (j >= 0 && j < G->vertices)) {
        // Set edge weight
        G->matrix[i][j] = k;
        if (G->undirected == true) {
            G->matrix[j][i] = k;
        }
        return true;
    } else {
        return false;
    }
}

// Check if the graph has an edge
bool graph_has_edge(Graph *G, uint32_t i, uint32_t j) {

    // Check if the vertices are within bounds and the edge weight is valid
    if ((i >= 0 && i < G->vertices) && (j >= 0 && j < G->vertices) && (G->matrix[i][j] > 0)) {
        return true;
    }

    else {
        return false;
    }
}

uint32_t graph_edge_weight(Graph *G, uint32_t i, uint32_t j) {

    // Check if the vertices are within bounds and edge weight is valid
    if ((i >= 0 && i < G->vertices) && (j >= 0 && j < G->vertices) && (G->matrix[i][j] > 0)) {
        return G->matrix[i][j];
    }

    else {
        return 0;
    }
}

// Check if graph vertex has been visited
bool graph_visited(Graph *G, uint32_t v) {

    if (G->visited[v] == true) {
        return true;
    }

    else {
        return false;
    }
}

// Mark a graph vertex as visited
void graph_mark_visited(Graph *G, uint32_t v) {
    // Make sure vertex is within bounds
    if (v >= 0 && v < G->vertices) {
        G->visited[v] = true;
    }
}

// Mark a graph vertex as unvisited
void graph_mark_unvisited(Graph *G, uint32_t v) {
    // Make sure vertex is within bounds
    if (v >= 0 && v < G->vertices) {
        G->visited[v] = false;
    }
}

// Print the graph
void graph_print(Graph *G) {
    uint32_t row;
    uint32_t column;
    // Make sure the max number of rows doesn't exceed the number of vertices in the graph
    for (row = 0; row < G->vertices; row++) {
        // Make sure the max number of columns doesn't exceed the number of vertices in the graph
        for (column = 0; column < G->vertices; column++) {
            // Print the current edge weight
            printf("%d ", G->matrix[row][column]);
        }
        printf("\n");
    }
}
