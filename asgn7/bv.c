#include "bv.h"
#include <stdbool.h>
#include <stdint.h>
#include <inttypes.h>
#include <stdlib.h>
#include <stdio.h>
#define BITS_PER_UNIT 8

// Used the bitwise operators and shifts code for bv_set_bit, bv_clr_bit, and bv_get_bit from the
// example provided by Dr. Long in the CSE 13S Code Comments bv8.h file
// Also got bv_create and bv_delete from Dr. Long's bv8.h file

struct BitVector {
    uint32_t length;
    uint8_t *vector;
};

// Got this function from the bv8.h file by Dr. Long
BitVector *bv_create(uint32_t length) {
    BitVector *bv = (BitVector *) malloc(sizeof(BitVector));
    if (bv) {
        uint32_t bytes = length / BITS_PER_UNIT + (length % BITS_PER_UNIT ? 1 : 0);
        bv->vector = (uint8_t *) calloc(bytes, sizeof(uint8_t));
        bv->length = length;
        return bv;
    } else {
        return (BitVector *) 0;
    }
}

// Got this function from Dr. Long in bv8.h
void bv_delete(BitVector **bv) {
    // Check if bv exists, then free its contents if it does
    if (*bv && (*bv)->vector) {
        free((*bv)->vector);
    }
    if (*bv) {
        free(*bv);
        *bv = NULL;
    }
}

// Return the BitVector's length
uint32_t bv_length(BitVector *bv) {
    return bv->length;
}

// Set a bit in the vector to 1
bool bv_set_bit(BitVector *bv, uint32_t i) {

    // Make sure i is within bounds
    if (i < 0 || i >= (bv->length)) {
        return false;
    } else if (bv && bv->vector) {
        // Got this from the bv8.h file by Dr. Long
        bv->vector[i / BITS_PER_UNIT] |= (0x1 << i % BITS_PER_UNIT);
    }
    return true;
}

// Set a bit in the vector to 0
bool bv_clr_bit(BitVector *bv, uint32_t i) {

    // Make sure i is within bounds
    if (i < 0 || i >= (bv->length)) {
        return false;
    } else if (bv && bv->vector) {
        // Got this from the bv8.h file by Dr. Long
        bv->vector[i / BITS_PER_UNIT] &= ~(0x1 << i % BITS_PER_UNIT);
    }
    return true;
}

// Find the value of a bit in the vector
bool bv_get_bit(BitVector *bv, uint32_t i) {

    // Make sure i is within bounds
    if (i < 0 || i >= (bv->length)
        || ((bv->vector[i / BITS_PER_UNIT] >> i % BITS_PER_UNIT) & 0x1) == 0) {
        return false;
    }
    // Got this from the bv8.h file by Dr. Long
    else if (((bv->vector[i / BITS_PER_UNIT] >> i % BITS_PER_UNIT) & 0x1) == 1) {
        return true;
    }
    return true;
}

// Print the length and the value of all the bits
void bv_print(BitVector *bv) {
    printf("length: %d\n", bv->length);
    for (uint8_t i = 0; i < bv->length * 8; i++) {
        printf("bit value: %d\n", bv->vector[i]);
    }
}
