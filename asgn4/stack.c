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

// Create a Stack  with an allocated memory of size Stack
Stack *stack_create(uint32_t capacity) {
    Stack *s = (Stack *) malloc(sizeof(Stack));
    if (s) {
        // Initialize the values
        s->top = 0;
        s->capacity = capacity;
        // Free memory of size uint32_t for the items
        s->items = (uint32_t *) calloc(capacity, sizeof(uint32_t));
        if (!s->items) {
            free(s);
            s = NULL;
        }
    }
    return s;
}

// Delete the stack and free allocated memory
void stack_delete(Stack **s) {
    if (*s && (*s)->items) {
        free((*s)->items);
        free(*s);
        *s = NULL;
    }
    return;
}

// Check if the stack is empty
bool stack_empty(Stack *s) {

    if (s->top == 0) {
        return true;
    }

    else {
        return false;
    }
}

// Check if the stack is full
bool stack_full(Stack *s) {

    if (s->top == s->capacity) {
        return true;
    }

    else {
        return false;
    }
}

// Return the size of the stack
uint32_t stack_size(Stack *s) {
    return s->top;
}

// Push the new value x into the stack
bool stack_push(Stack *s, uint32_t x) {

    // If the capacity has been reached then don't push
    if (s->top == s->capacity) {
        return false;
    }

    else {
        // Sets the top value to x
        s->items[s->top] = x;
        // Increment the top value to a greater size
        s->top = s->top + 1;
        return true;
    }
}

// Pops a value from the stack and puts it in x
bool stack_pop(Stack *s, uint32_t *x) {

    // If the stack is empty then we can't pop a value
    if (s->top == 0) {
        return false;
    }

    else {
        // Decrement the top value
        s->top = s->top - 1;
        // Setting the value of x
        *x = s->items[s->top];
        return true;
    }
}

// Peek at the top value without popping it
bool stack_peek(Stack *s, uint32_t *x) {

    // If there are no values in the stack, there's nothing to peek at
    if (s->top == 0) {
        return false;
    }

    else {
        // Set x equal to the decremented top value
        *x = s->items[s->top - 1];
        return true;
    }
}

// Create a copy of a stack
void stack_copy(Stack *dst, Stack *src) {

    // If the stack capacity's are the same size then set dst equal to src
    //if (dst->capacity <= src->capacity) {
    for (uint32_t i = 0; i < src->capacity; i++) {
        dst->items[i] = src->items[i];
    }
    //}

    // Match the top values of dst and src
    dst->top = src->top;
}

// Print the values of the stack
void stack_print(Stack *s, FILE *outfile, char *cities[]) {
    // Go through all elements of the stack
    for (uint32_t i = 0; i < s->top; i++) {
        // Print the cities that correspond to the items to the outfile
        fprintf(outfile, "%s", cities[s->items[i]]);
        if (i + 1 != s->top) {
            fprintf(outfile, " -> ");
        }
    }
    fprintf(outfile, "\n");
}
