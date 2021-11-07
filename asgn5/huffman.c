#include "node.h"
#include "code.h"
#include "defines.h"
#include <stdint.h>

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
        Node *left = dequeue(q, &n);
        Node *right = dequeue(q, &n);
        Node *parent = node_join(left, right);
        enqueue(q, parent);
    }

    Node *root = dequeue(q, &n);
    return root;
}

void build_codes(Node *root, Code table[static ALPHABET]) {

}

void dump_tree(int outfile, Node *root) {

}

Node *rebuild_tree(uint16_t nbytes, uint8_t tree[static nbytes]) {

}

void delete_tree(Node **root) {

}
