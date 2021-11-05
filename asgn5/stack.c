#include "stack.h"
#include "defines.h"

#include <inttypes.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct Stack Stack;

// Create a Stack structure with various values
struct Stack {
    uint32_t top;
    uint32_t capacity;
    Node **items;
};

// Create a Stack with an allocated memory of size Stack
Stack *stack_create(uint32_t capacity) {    
    Stack *s = (Stack *) malloc(sizeof(Stack));
    if (s) {
        // Initialize the values
        s->top = 0;
        s->capacity = capacity;
        // Free memory of size uint32_t for the items
        s->*items = (uint32_t *) calloc(capacity, sizeof(uint32_t));
        if (!s->*items) {
            free(s);
            s = NULL;
        }
    }
    return s;
}

// Delete the stack and free allocated memory
void stack_delete(Stack **s) {
    if (*s && (*s)->*items) {
        free((*s)->*items);
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

// Push the new Node n into the stack
bool stack_push(Stack *s, Node *n) {

    // If the capacity has been reached then don't push
    if (s->top == s->capacity) {
        return false;
    }

    else {
        // Sets the top value to n
        s->items[s->top] = n;
        // Increment the top value to a greater size
        s->top = s->top + 1;
        return true;
    }
}

// Pops a value from the stack and puts it in n
bool stack_pop(Stack *s, Node **n) {

    // If the stack is empty then we can't pop a value
    if (s->top == 0) {
        return false;
    }

    else {
        // Decrement the top value
        s->top = s->top - 1;
        // Setting the value of x
        *n = s->items[s->top];
        return true;
    }
}

// Print the values of the stack
void stack_print(Stack *s) {
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

