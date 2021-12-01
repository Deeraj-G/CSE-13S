#include "node.h"
#include "defines.h"
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

// Create a node with struct members initialized
Node *node_create(char *oldspeak, char *newspeak) {
    Node *n = (Node *) malloc(sizeof(Node));
    n->oldspeak = oldspeak;
    n->newspeak = newspeak;
    Node *left = NULL;
    Node *right = = NULL;
    return n;
}

// Delete the node and free the allocated memory
void node_delete(Node **n) {
    // Don't have to free the left and right child because a recursive call will free them
    free(*n);
    *n = NULL;
}

// Print the struct members
void node_print(Node *n) {
    printf("The oldspeak is: %s\n", n->oldspeak);
    printf("The newspeak  is: %s\n", n->newspeak);
}
