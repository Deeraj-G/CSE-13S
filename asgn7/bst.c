#include "node.h"
#include <stdbool.h>
#include <stdint.h>
#include <inttypes.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define max(x, y) x > y ? x : y

// Got bst.c from tutor Eric Hernandez

extern uint64_t branches;

Node *bst_create(void) {
    return NULL;
}

uint32_t bst_height(Node *root) {
    if (root == NULL) {
        return 0;
    }
    return max(bst_height(root->left), bst_height(root->right)) + 1;
}

uint32_t bst_size(Node *root) {
    if (root == NULL) {
        return 0;
    }
    return bst_size(root->left) + bst_size(root->right) + 1;
}

Node *bst_find(Node *root, char *oldspeak) {
    Node *curr = root;
    if (root != NULL && oldspeak != NULL) {
        while (curr != NULL && strcmp(curr->oldspeak, oldspeak) != 0) {
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
    Node *a = root;
    Node *b = NULL;
    if (oldspeak != NULL) {
        while ((a != NULL) && (a->oldspeak != oldspeak)) {
            b = a;
            if (strcmp(a->oldspeak, oldspeak) > 0) {
                a = a->left;
            } else {
                a = a->right;
            }
        }
    }

    if (b == NULL) {
        b = node_create(oldspeak, newspeak);
    } else if (strcmp(b->oldspeak, oldspeak) > 0) {
        b->left = node_create(oldspeak, newspeak);
    } else {
        b->right = node_create(oldspeak, newspeak);
    }
    return b;
}

void bst_print(Node *root) {
    Node *a = root;
    a = a->left;
}

void bst_delete(Node **root) {
    if (&(*root) != NULL) {
        if ((*root)->left != NULL) {
            bst_delete(&(*root)->left);
        }
        if ((*root)->right != NULL) {
            bst_delete(&(*root)->right);
        }
        node_delete(&(*root));
    }
}
