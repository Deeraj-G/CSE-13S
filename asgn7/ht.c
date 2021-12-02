#include "bst.h"
#include "ht.h"
#include "salts.h"
#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <stdlib.h>

// Used tutor Eric Hernandez's pseudocode for most of ht.c

struct HashTable {
    uint64_t salt[2];
    uint32_t size;
    Node **trees;
};

// Got most of this function from tutor Eric Hernandez
HashTable *ht_create(uint32_t size) {
    HashTable *ht = (HashTable *) malloc(sizeof(HashTable));
    ht->salt[0] = SALT_HASHTABLE_LO;
    ht->salt[1] = SALT_HASHTABLE_HI;
    ht->trees = (Node **) calloc(size, sizeof(Node *));
    ht->size = size;
    return ht;
}

// Got this function from tutor Eric Hernandez
void ht_delete(HashTable **ht) {
    for (uint32_t i = 0; i < (*ht)->size; i++) {
        if ((*ht)->trees[i] != NULL) {
            bst_delete(&(*ht)->trees[i]);
        }
    }
    free((*ht)->trees);
    free(*ht);
    *ht = NULL;
}

uint32_t ht_size(HashTable *ht) {
    return ht->size;
}

/*
// Got this function from tutor Eric Hernandez
Node *ht_lookup(HashTable *ht, char *oldspeak) {
    

}

// Got this function from tutor Eric Hernandez
void ht_insert(HashTable *ht, char *oldspeak, char *newspeak) {
}

// Got this function from tutor Eric Hernandez
uint32_t ht_count(HashTable *ht) {
}

// Got this function from tutor Eric Hernandez
uint32_t ht_count(HashTable *ht) {
}

// Got this function from tutor Eric Hernandez
double ht_avg_bst_size(HashTable *ht) {
}


void ht_print(HashTable *ht) {
}
*/
