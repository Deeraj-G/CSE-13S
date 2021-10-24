#include "stack.h"

#include "vertices.h"

#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// I used code made by Dr. Long in the asgn4.pdf for some of the functions
// I based a few functions off of the descriptions for the functions in asgn4.pdf by Dr. Long

// Create a Stack structure with various values
struct Stack {
    uint32_t top;
    uint32_t capacity;
    uint32_t *items;
};

// 
Stack *stack_create(uint32_t capacity) {
    Stack *s = (Stack *) malloc(sizeof(Stack));
    if (s) {
        s->top = 0;
        s->capacity = capacity;
        s->items = (uint32_t *) calloc(capacity, sizeof(uint32_t));
        if (!s->items) {
            free(s);
            s = NULL;
        }
    }
    return s;
}

void stack_delete(Stack **s) {
    if (*s && (*s)->items) {
        free((*s)->items);
        free(*s);
        *s = NULL;
    }
    return;
}

bool stack_empty(Stack *s) {

    if (s->top == 0) {
        return true;
    }

    else {
        return false;
    }
}

bool stack_full(Stack *s) {

    if (s->top == s->capacity) {
        return true;
    }

    else {
        return false;
    }
}

uint32_t stack_size(Stack *s) {
    return s->top;
}

bool stack_push(Stack *s, uint32_t x) {

    if (s->top == s->capacity) {
        return false;
    }

    else {

        s->items[s->top] = x;
        s->top = s->top + 1;
        return true;
    }
}

bool stack_pop(Stack *s, uint32_t *x) {

    if (s->top == 0) {
        return false;
    }

    else {
        s->top = s->top - 1;
        *x = s->items[s->top];
        return true;
    }
}

bool stack_peek(Stack *s, uint32_t *x) {

    if (s->top == 0) {
        return false;
    }

    else {
        *x = s->items[s->top - 1];
        return true;
    }
}

void stack_copy(Stack *dst, Stack *src) {

    if (dst->capacity == src->capacity) {
        for (uint32_t i = 0; i < src->capacity; i++) {
            dst->items[i] = src->items[i];
        }
    }

    dst->top = src->top;
}

void stack_print(Stack *s, FILE *outfile, char *cities[]) {
    for (uint32_t i = 0; i < s->top; i++) {
        fprintf(outfile, "%s", cities[s->items[i]]);
        if (i + 1 != s->top) {
            fprintf(outfile, " -> ");
        }
    }
    fprintf(outfile, "\n");
}
