#include "node.h"
#include <stdbool.h>
#include <stdint.h>
#include "pq.h"
#include <stdio.h>
#include <stdlib.h>
#include "node.c"

// Used coding ideas from TA Christian Ocon's section to create struct members
// Used two functions from the stats.c file in asgn3 created by Dr. Long

typedef struct PriorityQueue PriorityQueue;

struct PriorityQueue {
    uint32_t size;
    uint32_t capacity;
    uint32_t head;
    uint32_t tail;
    Node **items;
};


PriorityQueue *pq_create(uint32_t capacity) {
    PriorityQueue *q = (PriorityQueue *) malloc(sizeof(PriorityQueue));
    q->items = (Node **) malloc(capacity * sizeof(Node));
    q->capacity = capacity;
    q->size = 0;
    q->head = 0;
    q->tail = 0;
}

void pq_delete(PriorityQueue **q) {
    free((*q)->items);
    (*q)->items = NULL;
    free(*q);
    *q = NULL;
}

bool pq_empty(PriorityQueue *q) {
    
    if (q->size == 0) {
        return true;
    }
    else {
        return false;
    }
}

bool pq_full(PriorityQueue *q) {
    
    if (q->size == q->capacity) {
        return true;
    }
    else {
        return false;
    }
}

uint32_t pq_size(PriorityQueue *q) {
    return q->size;
}

// Received the following two functions from the stats.c file created by Dr. Long for asgn3
int cmp(Node *x, Node *y) {
    
    if (frequency(x) < frequency(y)) {
        return -1;
    } 
    else if (frequency(x) > frequency(y)) {
        return 1;
    } 
    else {
        return 0;
    }
}

void swap(Node **x, Node **y) {
    Node *t = *x;
    *x = *y;
    *y = t;
}

// Copied parts of my code from heap.c in asgn3 for the following 2 functions
// This function returns the smaller child between the arguments first and last
uint32_t min_child(PriorityQueue *q, uint32_t first, uint32_t last) {
    
    uint32_t left = 2 * first;
    uint32_t right = left + 1;

    // Checks if the right value is >= last and checks if the right value is greater than the left value
    if (right <= last && frequency(q->items[right - 1]) < frequency(q->items[left - 1])) {
        return right;
    }   
    
    else {
        return left;
    }   
} 

void fix_heap(PriorityQueue *q, uint32_t first, uint32_t last) {

    bool found = false;
    uint32_t mother = first;
    Node *temp;

    // This variable is set equal to the lesser value between mother and last
    uint32_t least = min_child(q, mother, last);

    // This loop checks if the array elements at mother is less than least, and swaps the two elements if it is true
    while (mother <= (last / 2) && (found == false)) {
        
        // Check if the array value at mother is less than the array value at least
        if (frequency(q->items[mother - 1]) > frequency(q->items[least - 1])) {
            
            // Swap the node values of mother and least
            temp = q->items[mother - 1];
            q->items[mother - 1] = q->items[least - 1];
            q->items[least - 1] = temp;

            // Sets mother equal to least
            mother = least;
            
            // Recalculates least now that mother is equal to the previous value of least
            least = min_child(q, mother, last);
        } 
        else {
            found = true;
        }
    }
}

bool enqueue(PriorityQueue *q, Node *n) {

    if (q->size == q->capacity) {
        return false;
    }

    else {
        q->items[q->tail] = n;
        q->size += 1;
        fix_heap(q, q->head, q->tail);
        q->tail += 1;
        return true;
    }



}

bool dequeue(PriorityQueue *q, Node **n) {

}

void pq_print(PriorityQueue *q) {

}

