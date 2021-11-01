#include "defines.h"
#include "code.h"

#include <stdbool.h>
#include <stdint.h>
#include <inttypes.h>
#include <stdlib.h>
#include <stdio.h>

// Used the code for code_set_bit, code_clr_bit, and code_get_bit from the 
// example provided by Dr. Long in the CSE 13S Code Comments bv8.h file

Code code_init(void) {
    Code d;
    d.top = 0;
    for (uint8_t i = 0; i < d.top; i++) {
        d.bits[i] = 0;
    }
    return d;
}

uint32_t code_size(Code *c) {
    return c->top;
}

bool code_empty(Code *c) {
    
    if (c->top == 0) {
        return true;
    }
    else {
        return false;
    }
}

bool code_full(Code *c) {
    
    if (c->top == ALPHABET) {
        return true;
    }
    else {
        return false;
    }
}


bool code_set_bit(Code *c, uint32_t i) {
    
    if (i < 0 || i > ALPHABET) {
        return false;
    }
    else {
        c->bits[i] |= (0x1 << i % ALPHABET);
        return true;
    }
}

bool code_clr_bit(Code *c, uint32_t i) {
    if (i < 0 || i > ALPHABET) {
        return false;
    }
    else {
        c->bits[i] &= ~(0x1 << i % ALPHABET);
        return true;
    }
}

bool code_get_bit(Code *c, uint32_t i) {
    
    if (i < 0 || i > ALPHABET || c->bits[i] == 0) {
        return false;
    }
    else {
        return (c->bits[i] >> i % ALPHABET) & 0x1;    
    }
}

bool code_push_bit(Code *c, uint8_t bit) {

    if (c->top == ALPHABET) {
        return false;
    }
    else {
        c->bits[c->top] = bit;
        c->top = c->top + 1;
        return true;
    }
}

bool code_pop_bit(Code *c, uint8_t *bit) {
    
    if (c->top == 0) {
        return false;
    }
    else {
        c->top = c->top - 1;
        *bit = c->bits[c->top];
        return true;
    }
}

void code_print(Code *c) {
    printf("%d\n", c->top);
    for (uint8_t i = 0; i < c->top; i++) {
        printf("%d\n", c->bits[i]);
    }
}







