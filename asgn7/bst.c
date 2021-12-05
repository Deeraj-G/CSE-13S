#include "node.h"
#include <stdbool.h>
#include <stdint.h>
#include <inttypes.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
//#define max(x, y) x > y ? x : y

// Got bst_find, bst_insert, bst_height, bst_print, and max from Dr. Long's Lecture 18 slides
// Followed the inorder traversal example from Lecture 18 page 22
// Got bst_create and bst_delete from tutor Eric Hernandez

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
        if (strcmp(root->oldspeak, oldspeak) > 0) {
            return bst_find(root->left, oldspeak);
        }
        // If the current oldspeak is less lexicographically significant than argument oldspeak take the right node
        else if (strcmp(root->oldspeak, oldspeak) < 0) {
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
        if (strcmp(root->oldspeak, oldspeak) > 0) {
            branches += 1;
            root->left = bst_insert(root->left, oldspeak, newspeak);
        }
        // Else take the right node
        else if (strcmp(root->oldspeak, oldspeak) < 0) {
            branches += 1;
            root->right = bst_insert(root->right, oldspeak, newspeak);
        }
        // If there are duplicates of the oldspeak, return root
        return root;
    }
    // Return the newly created node
    return node_create(oldspeak, newspeak);
}

// Recursively print all the nodes
// Followed the inorder traversal example from Lecture 18 page 22
void bst_print(Node *root) {
    // Make sure the root isn't NULL
    if (root) {
        bst_print(root->left);
        node_print(root);
        bst_print(root->right);
    }
}

// Delete the binary search tree
// Used Dr. Long's code from Lecture 18 page 76 for this function
void bst_delete(Node **root) {
    // Make sure the root exists
    if (*root) {
        bst_delete(&(*root)->left);
        bst_delete(&(*root)->right);
        node_delete(root);
    }
}
