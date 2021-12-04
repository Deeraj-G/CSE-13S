#include "bv.h"
#include "bf.h"
#include "salts.h"
#include <stdbool.h>
#include <stdint.h>
#include <inttypes.h>
#include <stdlib.h>
#include <stdio.h>
#include "speck.h"

// Got everything except bf_create from tutor Eric Hernandez

struct BloomFilter {
    uint64_t primary[2]; // Primary hash function salt .
    uint64_t secondary[2]; // Secondary hash function salt .
    uint64_t tertiary[2]; // Tertiary hash function salt .
    BitVector *filter;
};

// Create a BloomFilter
BloomFilter *bf_create(uint32_t size) {
    BloomFilter *bf = (BloomFilter *) malloc(sizeof(BloomFilter));
    bf->primary[0] = SALT_PRIMARY_LO;
    bf->primary[1] = SALT_PRIMARY_HI;
    bf->secondary[0] = SALT_SECONDARY_LO;
    bf->secondary[1] = SALT_SECONDARY_HI;
    bf->tertiary[0] = SALT_HASHTABLE_LO;
    bf->tertiary[1] = SALT_HASHTABLE_HI;
    bf->filter = bv_create(size);
    return bf;
}

// Delete a BloomFilter
void bf_delete(BloomFilter **bf) {
    // Call bv_delete on BitVector filter
    bv_delete(&(*bf)->filter);
    // Free the allocated memory of the BloomFilter
    free(*bf);
    *bf = NULL;
}

// Return the size of the BitVector filter
uint32_t bf_size(BloomFilter *bf) {
    return bv_length(bf->filter);
}

// Inserts oldspeak into the BloomFilter
void bf_insert(BloomFilter *bf, char *oldspeak) {
    // Hash the oldspeak with the three salts
    // Set the bits at the indices of the underlying bit vector
    bv_set_bit(bf->filter, hash(bf->primary, oldspeak) % bf_size(bf));
    bv_set_bit(bf->filter, hash(bf->secondary, oldspeak) % bf_size(bf));
    bv_set_bit(bf->filter, hash(bf->tertiary, oldspeak) % bf_size(bf));
}

// Probe the BloomFilter for oldspeak
bool bf_probe(BloomFilter *bf, char *oldspeak) {
    // Returns true if the oldspeak is likely to have been added to the BloomFilter
    return (bv_get_bit(bf->filter, hash(bf->primary, oldspeak) % bf_size(bf))
            & bv_get_bit(bf->filter, hash(bf->secondary, oldspeak) % bf_size(bf))
            & bv_get_bit(bf->filter, hash(bf->tertiary, oldspeak) % bf_size(bf)));
}

// Return the number of set bits in the BloomFilter
uint32_t bf_count(BloomFilter *bf) {
    uint32_t count = 0;
    // Go through the entire BloomFilter
    for (uint32_t i = 0; i < bv_length(bf->filter); i++) {
        // Increment count by the current bit in the filter
        count += bv_get_bit(bf->filter, i);
    }
    return count;
}

// Print the contents of the BloomFilter
void bf_print(BloomFilter *bf) {
    uint32_t count;
    printf("Size of filter: %d/n", bf_size(bf));
    for (uint32_t i = 0; i < bv_length(bf->filter); i++) {
        count = bv_get_bit(bf->filter, i);
        printf("The current bit is: %d\n", count);
    }
}
