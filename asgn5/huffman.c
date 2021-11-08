#include "node.h"
#include "code.h"
#include "defines.h"
#include "huffman.h"
#include "pq.h"
#include "io.h"
#include "stack.h"
#include <inttypes.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdint.h>

// Used TA Eugene's pseudocode for build_tree from his section
// Based my build_codes function off of  Dr. Long's python pseudocode
// Based my dump_tree function off of Dr. Long's python pseudocode

static Code c;
static bool init = false;

Node *build_tree(uint64_t hist[static ALPHABET]) {

    Node *n;
    int count = 0;

    // Enqueue the node's symbol and frequency of the current histogram element
    for (int i = 0; i < ALPHABET; i++) {
        if (hist[i] > 0) {
            count += 1;
        }
    }

    PriorityQueue *q = pq_create(count);

    for (int i = 0; i < ALPHABET; i++) {
        // Create a node with the current symbol and frequency
        n = node_create(i, hist[i]);
        // Enqueue the node to the PriorityQueue
        enqueue(q, n);
    }

    while (pq_size(q) > 1) {
        // Dequeue a node and set Node *left equal to it
        Node *left;
        dequeue(q, &left);

        // Dequeue a node and set Node *right equal to it
        Node *right;
        dequeue(q, &right);

        // Enqueue the parent node of left and right to q
        Node *parent = node_join(left, right);
        enqueue(q, parent);
    }

    // Dequeue the root node
    Node *root;
    dequeue(q, &root);
    pq_delete(&q);
    return root;
}

// Based this function off of Dr. Long's python pseudocode
void build_codes(Node *root, Code table[static ALPHABET]) {
    uint8_t *bit = 0;

    // Initialize the Code c once
    if (init == false) {
        c = code_init();
        init = true;
    }

    // Check if the root exists
    if (root != NULL) {

        // If the node doesn't have a left or right child then it's a leaf
        if (root->left == NULL && root->right == NULL) {
            // The current Code c represent the path to the node and is the code for the node's symbol
            table[root->symbol] = c;
        }

        // The current node must be an interior node
        else {

            // Push a 0 to the code and recurse the left node
            code_push_bit(&c, 0);
            build_codes(root->left, &table[ALPHABET]);
            code_pop_bit(&c, bit);

            // Push a 1 to the code and recurse the right node
            code_push_bit(&c, 1);
            build_codes(root->right, &table[ALPHABET]);
            code_pop_bit(&c, bit);
        }
    }
}

// Based this function off of Dr. Long's python pseudocode
void dump_tree(int outfile, Node *root) {

    uint8_t l = 'L';
    uint8_t i = 'I';

    if (root) {

        // Recursively call dump_tree on the left and right nodes
        dump_tree(outfile, root->left);
        dump_tree(outfile, root->right);

        if (root->left == NULL && root->right == NULL) {
            // Write an L to the outfile
            write_bytes(outfile, &l, 1);
            // Write the leaf's symbol to the outfile
            write_bytes(outfile, &root->symbol, 1);
        }

        else {
            // Write an I to the outfile
            write_bytes(outfile, &i, 1);
        }
    }
}

Node *rebuild_tree(uint16_t nbytes, uint8_t tree[static nbytes]) {

    Stack *s = stack_create(nbytes);

    // Loop thorugh
    for (uint64_t i = 0; i < nbytes; i++) {

        if (tree[i] == 'L') {
            Node *leaf = node_create(tree[i + 1], 0);
            stack_push(s, leaf);
        }

        else if (tree[i] == 'I') {
            Node *interior;
            stack_pop(s, &interior);

            Node *right = interior;
            stack_pop(s, &interior);

            Node *left = interior;
            Node *parent = node_join(left, right);
            stack_push(s, parent);
        }
    }

    Node *root;
    stack_pop(s, &root);
    return root;
}

void delete_tree(Node **root) {

    if (*root) {

        delete_tree(&(*root)->left);
        delete_tree(&(*root)->right);

        node_delete(root);
    }
}
