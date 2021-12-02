#include "bv.h"
#include <stdbool.h>
#include <stdint.h>
#include <inttypes.h>
#include <stdlib.h>
#include <stdio.h>

// Used the bitwise operators and shifts code for bv_set_bit, bv_clr_bit, and bv_get_bit from the
// example provided by Dr. Long in the CSE 13S Code Comments bv8.h file

struct BitVector {
    uint32_t length;
    uint8_t *vector;
};

BitVector *bv_create(uint32_t length) {
    BitVector *bv = (BitVector *) malloc(sizeof(BitVector));
    if (!bv) {
        return NULL;
    } else {
        bv->length = length;
        bv->vector = 0;
        for (uint8_t i = 0; i < bv->length * 8; i++) {
            bv->vector[i] = 0;
        }
        return bv;
    }
}

void bv_delete(BitVector **bv) {
    if (*bv) {
        free(*bv);
        *bv = NULL;
    }
}

uint32_t bv_length(BitVector *bv) {
    return bv->length;
}

bool bv_set_bit(BitVector *bv, uint32_t i) {

    // Make sure i is within bounds
    if (i < 0 || i >= (bv->length * 8)) {
        return false;
    } else {
        // Got this from the bv8.h file by Dr. Long
        bv->vector[i / 8] |= (0x1 << i % 8);
        return true;
    }
}

bool bv_clr_bit(BitVector *bv, uint32_t i) {

    // Make sure i is within bounds
    if (i < 0 || i >= (bv->length * 8)) {
        return false;
    } else {
        // Got this from the bv8.h file by Dr. Long
        bv->vector[i / 8] &= ~(0x1 << i % 8);
        return true;
    }
}

bool bv_get_bit(BitVector *bv, uint32_t i) {

    // Make sure i is within bounds
    if (i < 0 || i >= (bv->length * 8) || ((bv->vector[i / 8] >> i % 8) & 0x1) == 0) {
        return false;
    }
    // Got this from the bv8.h file by Dr. Long
    else if (((bv->vector[i / 8] >> i % 8) & 0x1) == 1) {
        return true;
    }
    return true;
}

void bv_print(BitVector *bv) {
    printf("length: %d\n", bv->length);
    for (uint8_t i = 0; i < bv->length * 8; i++) {
        printf("bit value: %d\n", bv->vector[i]);
    }
}
