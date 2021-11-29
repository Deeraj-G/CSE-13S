#include "bst.h"
#include "ht.h"
#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <stdlib.h>


struct HashTable {
    uint64_t salt [2];
    uint32_t size ;
    Node ** trees ;
};

HashTable *ht_create(uint32_t size) {
    HashTable *ht = (HashTable *) malloc(sizeof(HashTable));
    ht->salt[0] = SALT_HASHTABLE_LO;
    ht->salt[1] = SALT_HASHTABLE_HI;
    // Create a Node *trees
}

