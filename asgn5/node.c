#include <inttypes.h>
#include "node.h"
#include "defines.h"
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

Node *node_create(uint8_t symbol, uint64_t frequency) {
    Node *n = (Node *) malloc(sizeof(Node));
    n->symbol = symbol;
    n->frequency = frequency;
}

void node_delete(Node **n) {
    free(*n);
    *n = NULL;
}

Node *node_join(Node *left, Node *right) {
    Node *parent = node_create('$', (left->frequency + right->frequency));
}

void node_print(Node *n) {
    printf("The symbol ASCII is: " "%" PRIu8 "\n", n->symbol);
    printf("The frequency is: " "%" PRIu64 "\n", n->frequency);
}

// Helper functions
uint64_t frequency(Node *n) {
    return n->frequency;
}

uint8_t symbol(Node *n) {
    return n->symbol;
}
