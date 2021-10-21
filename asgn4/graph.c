#include <stdio.h>
#include <stdbool.h>
#include <inttypes.h>
#include "vertices.h"

Grap *graph_create(uint32_t vertices, bool undirected) {
	Graph *G = (Graph *)calloc(1, sizeof(Graph));
	G->vertices = vertices;
	G->undirected = undirected;
	return G;
}

void graph_delete(Graph **G) {
	free (*G);
	*G = NULL;
	return;
}

struct Graph {
	uint32_t vertices;
	bool undirected;
	bool verified[VERTICES];
	uint32_t matrix[VERTICES][VERTICES];
}

