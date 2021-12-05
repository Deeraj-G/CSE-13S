#include "node.h"
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// Got node_print from the asgn7 pdf by Dr. Long
// Got the idea to do the if/else statement for n->oldspeak from tutor Eric Hernandez

// Create a node with struct members initialized
Node *node_create(char *oldspeak, char *newspeak) {

    Node *n = (Node *) malloc(sizeof(Node));

    if (n) {
        n->left = NULL;
        n->right = NULL;

        // I had the if/else statement for newspeak before going to tutor Eric Hernandez's section,
        // but going to the section informed me that I needed to do the same for oldspeak

        // If oldspeak is NULL, n->oldspeak should equal NULL
        if (oldspeak != NULL) {
            n->oldspeak = strdup(oldspeak);
        } else {
            n->oldspeak = NULL;
        }

        // If newspeak is NULL, n->newspeak should equal NULL
        if (newspeak != NULL) {
            n->newspeak = strdup(newspeak);
        } else {
            n->newspeak = NULL;
        }
    }
    return n;
}

// Delete the node and free the allocated memory
void node_delete(Node **n) {

    // Take care of the case where oldspeak equals NULL
    if ((*n)->oldspeak != NULL) {
        free((*n)->oldspeak);
    }
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
    }
    if ((n->oldspeak != NULL) && (n->newspeak == NULL)) {
        printf("%s\n", n->oldspeak);
    }
}
