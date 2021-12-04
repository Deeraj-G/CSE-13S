#include "bst.h"
#include "ht.h"
#include "salts.h"
#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <stdlib.h>
#include "speck.h"

// Used tutor Eric Hernandez's pseudocode for ht.c

struct HashTable {
    uint64_t salt[2];
    uint32_t size;
    Node **trees;
};

HashTable *ht_create(uint32_t size) {
    HashTable *ht = (HashTable *) malloc(sizeof(HashTable));
    ht->salt[0] = SALT_HASHTABLE_LO;
    ht->salt[1] = SALT_HASHTABLE_HI;
    ht->trees = (Node **) calloc(size, sizeof(Node *));
    ht->size = size;
    return ht;
}

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

Node *ht_lookup(HashTable *ht, char *oldspeak) {
    uint32_t index = hash(ht->salt, oldspeak) % ht->size;
    return bst_find(ht->trees[index], oldspeak);
}

void ht_insert(HashTable *ht, char *oldspeak, char *newspeak) {
    uint32_t index = hash(ht->salt, oldspeak) % ht->size;
    ht->trees[index] = bst_insert(ht->trees[index], oldspeak, newspeak);
}

uint32_t ht_count(HashTable *ht) {
    uint32_t count = 0;
    for (uint32_t i = 0; i < ht->size; i++) {
        if (ht->trees[i] != NULL) {
            count++;
        }
    }
    return count;
}

double ht_avg_bst_size(HashTable *ht) {
    double avg_size = 0;
    for (uint32_t i = 0; i < ht->size; i++) {
        avg_size = bst_size(ht->trees[i]);
    }
    return avg_size / ht_count(ht);
}

double ht_avg_bst_height(HashTable *ht) {
    double avg_height = 0;
    for (uint32_t i = 0; i < ht->size; i++) {
        avg_height += bst_height(ht->trees[i]);
    }
    return avg_height / ht_count(ht);
}

void ht_print(HashTable *ht) {
    printf("Hash Table Size: %d\n", ht_size(ht));
}
