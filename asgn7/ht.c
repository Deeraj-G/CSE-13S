#include "bst.h"
#include "ht.h"
#include "salts.h"
#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <stdlib.h>
#include "speck.h"

uint64_t lookups;

// Used tutor Eric Hernandez's pseudocode for ht.c

struct HashTable {
    uint64_t salt[2];
    uint32_t size;
    Node **trees;
};

// Create a HashTable
HashTable *ht_create(uint32_t size) {
    HashTable *ht = (HashTable *) malloc(sizeof(HashTable));
    ht->salt[0] = SALT_HASHTABLE_LO;
    ht->salt[1] = SALT_HASHTABLE_HI;
    ht->trees = (Node **) calloc(size, sizeof(Node *));
    ht->size = size;
    return ht;
}

// Delete a HashTable
void ht_delete(HashTable **ht) {
    if (*ht) {
        // Loop through the entire hash table
        for (uint32_t i = 0; i < (*ht)->size; i++) {
            // If the current node isn't empty, recursively delete its bst
            if ((*ht)->trees[i] != NULL) {
                bst_delete(&(*ht)->trees[i]);
            }
        }
        // Free the allocated memory for the nodes
        if ((*ht)->trees) {
            free((*ht)->trees);
        }
        // Free the allocated memory for the HashTable
        free(*ht);
        *ht = NULL;
    }
}

// Return the size of the HashTable
uint32_t ht_size(HashTable *ht) {
    return ht->size;
}

// Search the hash table for a node that contains argument oldspeak
Node *ht_lookup(HashTable *ht, char *oldspeak) {
    // Set the index to the hashed oldspeak
    uint32_t index = hash(ht->salt, oldspeak) % ht->size;
    // Go through the current bst and see if there are any Nodes with oldspeak that match the argument
    lookups += 1;
    return bst_find(ht->trees[index], oldspeak);
}

// Insert a new node into a bst
void ht_insert(HashTable *ht, char *oldspeak, char *newspeak) {
    // Set the index to the hashed oldspeak
    uint32_t index = hash(ht->salt, oldspeak) % ht->size;
    // Insert the new Node in the correct position in the bst, store the result in the index element of the HashTable
    lookups += 1;
    ht->trees[index] = bst_insert(ht->trees[index], oldspeak, newspeak);
}

// Return the number of non-NULL bst's in the HashTable
uint32_t ht_count(HashTable *ht) {
    uint32_t count = 0;
    // Go through the entire HashTable
    for (uint32_t i = 0; i < ht->size; i++) {
        // Increment the count if the current element isn't NULL
        if (ht->trees[i] != NULL) {
            count++;
        }
    }
    return count;
}

// Return the average bst size
double ht_avg_bst_size(HashTable *ht) {
    double avg_size = 0;
    // Go through the entire HashTable
    for (uint32_t i = 0; i < ht->size; i++) {
        // Calculate the average by summing the sizes of each bst in the HashTable
        avg_size += bst_size(ht->trees[i]);
    }
    // Then divide the sum by the number of non-NULL bst's in the HashTable
    return avg_size / ht_count(ht);
}

// Calculate the average bst height
double ht_avg_bst_height(HashTable *ht) {
    double avg_height = 0;
    // Go through the entire HashTable
    for (uint32_t i = 0; i < ht->size; i++) {
        // Sum the heights of each bst in the HashTable
        avg_height += bst_height(ht->trees[i]);
    }
    // Divide the sum by the number of non-NULL bst's in the HashTable
    return avg_height / ht_count(ht);
}

// Print the values in the HashTable
void ht_print(HashTable *ht) {
    printf("Hash Table Size: %d\n", ht_size(ht));
}
