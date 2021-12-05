#include "node.h"
#include <stdbool.h>
#include <stdint.h>
#include <inttypes.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
//#define max(x, y) x > y ? x : y

// Got everything except bst_find, bst_insert, and max from tutor Eric Hernandez
// Got bst_find from Dr. Long's Lecture 18 slides on page 57
uint64_t branches;

Node *bst_create(void) {
    return NULL;
}

// Got this function from Dr. Long on Lecture 18 page 55
static int max(int x, int y) {
    return x > y ? x : y;
}

// Used Dr. Long's code from Lecture 18 slide 55 for this function
uint32_t bst_height(Node *root) {
    // If the root node is NULL, then there is no bst
    if (root) {
        return 1 + max(bst_height(root->left), bst_height(root->right));
    }
    return 0;
}

uint32_t bst_size(Node *root) {
    // Make sure the root node exists
    if (root == NULL) {
        return 0;
    }
    // Return the size of the entire bst
    return bst_size(root->left) + bst_size(root->right) + 1;
}

// Used the Professor's code from the Lecture 18 slides on page 57 for this function
Node *bst_find(Node *root, char *oldspeak) {
    // Make sure the root node isn't NULL
    if (root) {
        // If the current oldspeak is more lexicographically significant than argument oldspeak take the left node
        if (root->oldspeak > oldspeak) {
            return bst_find(root->left, oldspeak);
        }
        // If the current oldspeak is less lexicographically significant than argument oldspeak take the right node
        else if (root->oldspeak < oldspeak) {
            return bst_find(root->right, oldspeak);
        }
    }
    return root;
}

// Used Dr. Long's code from Lecture 18 page 62 for this function
Node *bst_insert(Node *root, char *oldspeak, char *newspeak) {
    // Make sure root isn't NULL
    if (root) {
        // If the current oldspeak is more lexicographically significant than argument oldspeak take the left node
        if (root->oldspeak > oldspeak) {
            root->left = bst_insert(root->left, oldspeak, newspeak);
        }
        // Else take the right node
        else {
            root->right = bst_insert(root->right, oldspeak, newspeak);
        }
        // If there are duplicates of the oldspeak, return root
        return root;
    }
    // Return the newly created node
    return node_create(oldspeak, newspeak);
}

// Print the root node
void bst_print(Node *root) {
    node_print(root);
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
