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
    } else if (x > y) {
        return 1;
    } else {
        return 0;
    }
}

void swap(Node *x, Node *y) {
    // FIX SWAP
    Node *t = x;
    *x = *y;
    *y = *t;
}

// Copied parts of my code from heap.c in asgn3 for the following 2 functions
// This function returns the smaller child between the arguments first and last
uint32_t min_child(Node *n, PriorityQueue *q, uint32_t first, uint32_t last) {

    uint32_t left = 2 * first;
    uint32_t right = left + 1;

    // Checks if the right value is >= last and checks if the right value is less than the left value
    if (right <= last && ((cmp(q->items[right - 1], q->items[left - 1])) > 0)) {

    //if (right >= last && (A[right - 1] < A[left - 1])) {
        return right;
    }   
    
    else {
        return left;
    }   
} 


// This function fixes the heap so it obeys the constraints of a heap after the smallest element has been removed
void fix_heap(Node *n, PriorityQueue *q, uint32_t first, uint32_t last) {

    bool found = false;
    uint32_t mother = first;
    
    // This variable is set equal to the greater value between mother and last
    uint32_t great = min_child(n, q, mother, last);

    // This loop checks if the array elements at mother is less than great, and swaps the two elements if it is true
    while (mother <= (last / 2) && (found == false)) {
        
        // Check if the array value at mother is less than the array value at great
        if ((cmp(q->items[mother - 1], q->items[great - 1])) < 0) {
        
            // Swap the elements of mother and great
            swap(q->items[first - 1], q->items[great - 1]);
            
            // Sets mother equal to great
            mother = great;
            
            // Recalculates great now that mother is equal to the previous value of great
            great = min_child(n, q, mother, last);
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
        fix_heap(n, q, q->head, q->tail);
        q->tail += 1;
        return true;
    }



}

bool dequeue(PriorityQueue *q, Node **n) {

}

void pq_print(PriorityQueue *q) {

}

