#include "defines.h"
#include "code.h"

#include <stdbool.h>
#include <stdint.h>
#include <inttypes.h>

typedef struct {
    uint32_t top;
    uint8_t bits[MAX_CODE_SIZE];
} Code;

Code code_init(void) {
    Code->top = 0;
    for (uint8_t i = 0; i < Code->top; i++) {
        Code->bits[i] = 0;
    }
    return Code;
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
        c->bits[i] = 1;
        return true;
    }
}

bool code_clr_bit(Code *c, uint32_t i) {
    if (i < 0 || i > ALPHABET) {
        return false;
    }
    else {
        c->bits[i] = 0;
        return true;
    }
}

bool code_get_bit(Code *c, uint32_t i) {
    
    if (i < 0 || i > ALPHABET || c->bits[i] == 0) {
        return false;
    }
    else if (c->bits[i] == 1) {
        return true;
    }
}

bool code_push_bit(Code *c, uint8_t bit) {

    if (c->top == ALPHABET) {
        return false;
    }
    else {
        c->bits[top + 1] = bit;
        return true;
}

bool code_pop_bit(Code *c, uint8_t *bit) {
    
    if (c->top == 0) {
        return false;
    }
    else {
        *bit = c->bits[top - 1];
        return true;
    }
}

void code_print(Code *c) {
    for (uint8_t i = 0; i < c->top; i++) {
        printf("%d\n", c->top); 
        printf("%d\n", c->bits[i]);
    }
}







