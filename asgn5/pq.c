#include "node.h"
#include <stdbool.h>
#include <stdint.h>
#include "pq.h"
#include <stdio.h>
#include <stdlib.h>

// Used coding ideas from TA Christian Ocon's section to create struct members
// Used two functions from the stats.c file in asgn3 created by Dr. Long
// Used the pseudocode for the while loop in enqueue from TA Eugene's section

typedef struct PriorityQueue PriorityQueue;

// Initialized some more struct members
struct PriorityQueue {
    uint32_t size;
    uint32_t capacity;
    //    uint32_t head;
    //    uint32_t tail;
    Node **items;
};

// Create a PriorityQueue
PriorityQueue *pq_create(uint32_t capacity) {
    PriorityQueue *q = (PriorityQueue *) malloc(sizeof(PriorityQueue));
    q->items = (Node **) malloc(capacity * sizeof(Node));
    q->capacity = capacity;
    q->size = 0;
    //    q->head = 0;
    //    q->tail = 0;
    return q;
}

// Delete a PriorityQueue and free up the allocated memory
void pq_delete(PriorityQueue **q) {
    free((*q)->items);
    //    (*q)->items = NULL;
    free(*q);
    *q = NULL;
}

// Check if the PriorityQueue is empty
bool pq_empty(PriorityQueue *q) {

    if (q->size == 0) {
        return true;
    } else {
        return false;
    }
}

// Check if the PriorityQueue is full
bool pq_full(PriorityQueue *q) {

    if (q->size == q->capacity) {
        return true;
    } else {
        return false;
    }
}

// Return the size of the PriorityQueue
uint32_t pq_size(PriorityQueue *q) {
    return q->size;
}

// Copied parts of my code from heap.c in asgn3 for the following 2 functions
// This function returns the smaller child between the arguments first and last
uint32_t min_child(PriorityQueue *q, uint32_t first, uint32_t last) {

    uint32_t left = 2 * first;
    uint32_t right = left + 1;

    // Checks if the right value is >= last and checks if the right value is greater than the left value
    if ((right <= last) && q->items[right - 1]->frequency < q->items[left - 1]->frequency) {
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
    while ((mother <= (last / 2)) && found == false) {
        // Check if the array value at mother is less than the array value at least
        if (q->items[mother - 1]->frequency > q->items[least - 1]->frequency) {

            // Swap the node values of mother and least
            temp = q->items[mother - 1];
            q->items[mother - 1] = q->items[least - 1];
            q->items[least - 1] = temp;

            // Sets mother equal to least
            mother = least;

            // Recalculates least now that mother is equal to the previous value of least
            least = min_child(q, mother, last);
        } else {
            found = true;
        }
    }
}

bool enqueue(PriorityQueue *q, Node *n) {
    uint32_t k;
    uint32_t parent;

    if (q->size == q->capacity) {
        return false;
    } else {
        q->items[q->size] = n;
    }

    q->size += 1;
    k = q->size;

    // Got the basic pseudocode for the while loop from TA Eugene's section
    // Fix the heap after enqueueing
    while (k > 1) {
        parent = k / 2;
        fix_heap(q, parent, q->size);
        k = parent;
    }
    return true;
}

bool dequeue(PriorityQueue *q, Node **n) {
    Node *temp2;
    uint32_t k;
    uint32_t parent;

    // If the queue is empty, there's nothing to dequeue
    if (q->size == 0) {
        return false;
    }

    // Store the dequeued element in the pointer
    *n = q->items[0];

    // Swap the first and last elements in q->items
    temp2 = q->items[0];
    q->items[0] = q->items[q->size - 1];
    q->items[q->size - 1] = temp2;

    // Decrement the size to effectively get rid of the dequeued element
    q->size -= 1;

    k = q->size;

    // Got the basic pseudocode for the while loop from TA Eugene's section
    // Fix the heap after dequeueing
    while (k > 1) {
        parent = k / 2;
        fix_heap(q, parent, q->size);
        k = parent;
    }

    return true;
}

void pq_print(PriorityQueue *q) {
    for (uint32_t i = 0; i < q->size; i++) {
        printf("Priority Queue contents: %ld\n", q->items[i]->frequency);
    }
}
