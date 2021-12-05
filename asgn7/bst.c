#include "node.h"
#include <stdbool.h>
#include <stdint.h>
#include <inttypes.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define max(x, y) x > y ? x : y

// Got bst.c from tutor Eric Hernandez

uint64_t branches;

Node *bst_create(void) {
    return NULL;
}

uint32_t bst_height(Node *root) {
    // If the root node is NULL, then there is no bst
    if (root == NULL) {
        return 0;
    }
    // Else return the max height of the bst
    return max(bst_height(root->left), bst_height(root->right)) + 1;
}

uint32_t bst_size(Node *root) {
    // Make sure the root node exists
    if (root == NULL) {
        return 0;
    }
    // Return the size of the entire bst
    return bst_size(root->left) + bst_size(root->right) + 1;
}

Node *bst_find(Node *root, char *oldspeak) {
    // Set curr equal to the root
    Node *curr = root;
    // If the root node exists and the oldspeak exists then execute the rest of the code
    if (root != NULL && oldspeak != NULL) {
        // Make sure the current node exists and there aren't any duplicates in the code
        while (curr != NULL && strcmp(curr->oldspeak, oldspeak) != 0) {
            // If the current oldspeak is more lexicographically significant than oldspeak take the left node
            if (strcmp(curr->oldspeak, oldspeak) > 0) {
                curr = curr->left;
            } else {
                curr = curr->right;
            }
        }
    }
    return curr;
}

Node *bst_insert(Node *root, char *oldspeak, char *newspeak) {
    // Initialize a as the root node
    Node *a = root;
    Node *b = NULL;
    // Make sure the oldspeak isn't NULL
    if (oldspeak != NULL) {
        // Make sure there aren't any duplicates of the oldspeak
        while ((a != NULL) && (strcmp(a->oldspeak, oldspeak) != 0)) {
            // Set Node b as the the value of a before it equals the node's children
            b = a;
            // If the current oldspeak is more lexicographically significant than oldspeak take the left node
            if (strcmp(a->oldspeak, oldspeak) > 0) {
                a = a->left;
            } else {
                a = a->right;
            }
        }
    }

    // If b is NULL, set it's current position as a new node
    if (b == NULL) {
        b = node_create(oldspeak, newspeak);
    }
    // If b's oldspeak is more lexicographically significant than argument oldspeak set the left node as the new node
    else if (strcmp(b->oldspeak, oldspeak) > 0) {
        b->left = node_create(oldspeak, newspeak);
    }
    // If b's oldspeak is less lexicographically significant than argument oldspeak set the right node as the new node
    else {
        b->right = node_create(oldspeak, newspeak);
    }
    return b;
}

// Make an actual print statement later
void bst_print(Node *root) {
    Node *a = root;
    a = a->left;
}

// Delete the binary search tree
void bst_delete(Node **root) {
    // Make sure the root exists
    if (&(*root) != NULL) {
        // Make sure the left root exists before deleting it
        if ((*root)->left != NULL) {
            bst_delete(&(*root)->left);
        }
        // Make sure the right root exists before deleting it
        if ((*root)->right != NULL) {
            bst_delete(&(*root)->right);
        }
        // Delete the root node once the left and right side have been recursively deleted
        node_delete(&(*root));
    }
}
