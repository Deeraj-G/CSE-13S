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

bool stack_empty(Stack *s) {


}

bool stack_full(Stack *s) {

}

uint32_t stack_size(Stack *s) {

}

bool stack_push(Stack *s, uint32_t x) {

}

bool stack_pop(Stack *s, uint32_t *x) {

}

bool stack_peek(Stack *s, uint32_t *x) {

}

void stack_copy(Stack *dst, Stack *src) {

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
