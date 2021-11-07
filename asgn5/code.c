#include "defines.h"
#include "code.h"

#include <stdbool.h>
#include <stdint.h>
#include <inttypes.h>
#include <stdlib.h>
#include <stdio.h>

// Used the bitwise operators and shifts code for code_set_bit, code_clr_bit, and code_get_bit from the
// example provided by Dr. Long in the CSE 13S Code Comments bv8.h file, though I've made a couple modifications

// Create a Code
// Got the d.top idea from TA Christian Ocan's section
Code code_init(void) {
    Code d;
    d.top = 0;
    for (uint8_t i = 0; i < d.top; i++) {
        d.bits[i] = 0;
    }
    return d;
}

// Return the code size
uint32_t code_size(Code *c) {
    return c->top;
}

// Check if the code is empty
bool code_empty(Code *c) {

    if (c->top == 0) {
        return true;
    } else {
        return false;
    }
}

// Check if the code is full
bool code_full(Code *c) {

    if (c->top == ALPHABET) {
        return true;
    } else {
        return false;
    }
}

// Set a bit inside of the bits array to 1
bool code_set_bit(Code *c, uint32_t i) {

    if (i < 0 || i > ((c->top) * 8)) {
        return false;
    } else {
        // Got this from the bv8.h file by Dr. Long
        c->bits[i / 8] |= (0x1 << i % 8);
        return true;
    }
}

// Set a bit inside of the bits array to 0
bool code_clr_bit(Code *c, uint32_t i) {

    if (i < 0 || i > (c->top) * 8) {
        return false;
    } else {
        // Got this from the bv8.h file by Dr. Long
        c->bits[i / 8] &= ~(0x1 << i % 8);
        return true;
    }
}

// Get a bit from the bits array
bool code_get_bit(Code *c, uint32_t i) {

    if (i < 0 || i > (c->top) * 8 || c->bits[i / 8] == 0) {
        return false;
    } else if (c->bits[i / 8] == 1) {
        // Got this from the bv8.h file by Dr. Long
        (c->bits[i / 8] >> i % 8) & 0x1;
        return true;
    }
}

// Push a bit onto the Code
bool code_push_bit(Code *c, uint8_t bit) {

    if (c->top == ALPHABET) {
        return false;
    }

    else if (bit > 0) {
        // If the bit value is 1 then set the top value of Code c
        code_set_bit(c, c->top);
        c->top += 1;
    }

    else if (bit == 0) {
        // If the bit value is 0 then clear the top value of Code c
        code_clr_bit(c, c->top);
        c->top += 1;
    }
    return true;
}

// Pop a bit from the Code
bool code_pop_bit(Code *c, uint8_t *bit) {

    if (c->top == 0) {
        return false;
    } else {
        c->top = c->top - 1;
        *bit = code_get_bit(c, c->top);
        return true;
    }
}

// Print the value of each bit inside of the bits array
void code_print(Code *c) {
    printf("%d\n", c->top);
    for (uint8_t i = 0; i < c->top; i++) {
        printf("%d\n", c->bits[i]);
    }
}
