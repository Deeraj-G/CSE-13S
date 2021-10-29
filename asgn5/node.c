#include <inttypes.h>
#include "node.h"
#include "defines.h"

typedef struct Node Node; 

struct Node {
    Node *left;
    Node *right;
    uint8_t symbol;
    uint64_t frequency;
};

Node *node_create(uint8_t symbol, uint64_t frequency) {
    Node *n = (Node *) malloc(sizeof(Node));
    n->symbol = symbol;
    n->frequency = frequency;
}

void node_delete(Node **n) {
    if (*n && (*n)->*left && (*n)->*right) {
        //free((*n)->*left);
        //free((*n)->*right);
        free(*n);
        *n = NULL;

    }

}

Node *node_join(Node *left, Node *right) {
    Node parent = node_create("$", left->frequency + right->frequency);
}

void node_print(Node *n) {
    printf("parent: %d, %d\n", n->symbol, n->frequency);
    printf("left: %d, %d\n", left->symbol, left->frequency);
    printf("right: %d, %d\n", right->symbol, right->frequency);
}
