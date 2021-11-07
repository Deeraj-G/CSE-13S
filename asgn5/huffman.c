#include "node.h"
#include "code.h"
#include "defines.h"
#include <stdint.h>
#include "huffman.h"
#include <inttypes.h>

#include "node.c"
#include "pq.c"

// Used TA Eugene's pseudocode for build_tree from his section
// Used Dr. Long's python pseudocode for build_codes 

Node *build_tree(uint64_t hist[static ALPHABET]) {
    int count;

    // Create a priority queue of nodes whose frequency is non-zero
    for (int i = 0; i < ALPHABET; i++) {
        if (hist[i] > 0) {
            count += 1;
        }
    }

    PriorityQueue *q = pq_create(total);

    for (int i = 0; i < ALPHABET; i++) {
        // Create a node with the current symbol and frequency    
        Node *n = node_create(i, hist[i]);
        // Enqueue the node to the PriorityQueue
        enqueue(q, n);
    }
    
    while (pq_size(q) > 1) {
        // Dequeue a node and set Node *left equal to it
        dequeue(q, &n);
        Node *left = n;
        
        // Dequeue a node and set Node *right equal to it
        dequeue(q, &n);
        Node *right = n;
        
        // Enqueue the parent node of left and right to q
        Node *parent = node_join(left, right);
        enqueue(q, parent);
    }

    // Dequeue the root node
    dequeue(q, &n);
    Node *root = n;
    return root;
}

void build_codes(Node *root, Code table[static ALPHABET]) {
    Code c = code_init();
    uint8_t *bit;

    if (root != 0) {
        
        if (!(root->left) && !(root->right)) {
            table[symbol(root)] = c;
        }

        else {
            code_push_bit(c, 0);
            build_codes(root->left, Code table[static ALPHABET]);
            code_pop_bit(c, bit);

            code_push_bit(c, 1);
            build_codes(root->right, Code table[static ALPHABET]);
            code_pop_bit(c, bit);
        }
    }
}

void dump_tree(int outfile, Node *root) {

}

Node *rebuild_tree(uint16_t nbytes, uint8_t tree[static nbytes]) {

}

void delete_tree(Node **root) {













































}
