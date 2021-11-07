#include <inttypes.h>
#include "node.h"
#include "defines.h"
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

// Create a node with struct members initialized
Node *node_create(uint8_t symbol, uint64_t frequency) {
    Node *n = (Node *) malloc(sizeof(Node));
    n->symbol = symbol;
    n->frequency = frequency;
    return n;
}

// Delete the node and free the allocated memory
void node_delete(Node **n) {
    free(*n);
    *n = NULL;
}

// Create a parent node whose frequency is the sum of the children's frequency
Node *node_join(Node *left, Node *right) {
    Node *parent = node_create('$', (left->frequency + right->frequency));
    return parent;
}

// Print the struct members
void node_print(Node *n) {
    printf("The symbol ASCII is: "
           "%" PRIu8 "\n",
        n->symbol);
    printf("The frequency is: "
           "%" PRIu64 "\n",
        n->frequency);
}

// Helper functions
// Returns the frequency of a Node
uint64_t frequency(Node *n) {
    return n->frequency;
}

// Returns the symbol of a Node
uint8_t symbol(Node *n) {
    return n->symbol;
}
