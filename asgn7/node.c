#include "node.h"
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// Got node_print from the asgn7 pdf by Dr. Long

// Create a node with struct members initialized
Node *node_create(char *oldspeak, char *newspeak) {
    Node *n = (Node *) malloc(sizeof(Node));
    n->oldspeak = strdup(oldspeak);
    if (newspeak != NULL) {
        n->newspeak = strdup(newspeak);
    } else {
        n->newspeak = NULL;
    }
    n->left = NULL;
    n->right = NULL;
    return n;
}

// Delete the node and free the allocated memory
void node_delete(Node **n) {
    free((*n)->oldspeak);
    // Take care of the case where newspeak equals NULL
    if ((*n)->newspeak != NULL) {
        free((*n)->newspeak);
    }
    free(*n);
    *n = NULL;
}

// Print the struct members
void node_print(Node *n) {
    if ((n->oldspeak != NULL) && (n->newspeak != NULL)) {
        printf("%s -> %s\n", n->oldspeak, n->newspeak);
    } else if ((n->oldspeak != NULL) && (n->newspeak == NULL)) {
        printf("%s\n", n->oldspeak);
    }
}
