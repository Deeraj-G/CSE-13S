#include "stack.h"
#include "vertices.h"
#include <stdio.h>
#include <stdbool.h>
#include <inttypes.h>

// I used code made by Dr. Long in the asgn4.pdf
// I based my code off of the descriptions for the functions in asgn4.pdf by Dr. Long

struct Stack {
    uint32_t top;
    uint32_t capacity;
    uint32_t *items;
};

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


