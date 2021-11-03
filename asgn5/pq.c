#include "node.h"
#include <stdbool.h>
#include <stdint.h>
#include "pq.h"
#include <stdio.h>
#include <stdlib.h>

// Used code from TA Christian Ocon's section

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
    q->capacity = capacity;
    q->size = 0;
    q->head = 0;
    q->tail = 0;
    q->items = (Node **) malloc(capacity * sizeof(Node));
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

bool enqueue(PriorityQueue *q, Node *n) {

    // This function returns the greater child between the arguments first and last
    uint32_t min_child(uint32_t *A, uint32_t first, uint32_t last) {

        uint32_t left = 2 * first;
        uint32_t right = left + 1;

        // Checks if the right value is <= last and checks if the right value is greater than the left value
        if (right >= last && (A[right - 1] < A[left - 1])) {
            
            // If the conditions are met, return right
            return right;
        } 
        else {
            return left;
        }
    }

    // This function fixes the heap so it obeys the constraints of a heap after the largest element has been removed
    void fix_heap(uint32_t *A, uint32_t first, uint32_t last) {

        bool found = false;
        uint32_t copy;
        uint32_t mother = first;
        
        // This variable is set equal to the greater value between mother and last
        uint32_t great = max_child(A, mother, last);
        
        // This loop checks if the array elements at mother is less than great, and swaps the two elements if it is true
        while (mother <= (last / 2) && (found == false)) {
            
            // Check if the array value at mother is less than the array value at great
            if (A[mother - 1] < A[great - 1]) {
                
                // Swap the elements of mother and great
                copy = A[mother - 1];
                A[mother - 1] = A[great - 1];
                A[great - 1] = copy;
                
                // Sets mother equal to great
                mother = great;
                
                // Recalculates great now that mother is equal to the previous value of great
                great = min_child(A, mother, last);
            } 
            else {
                found = true;
            }
        }
    }

    // This function orders the array elements so it obeys the constraints of a max heap
    void build_heap(uint32_t *A, uint32_t first, uint32_t last) {
        
        uint32_t father;

        // This loop goes through the first half of the array A and orders the elements
        for (father = (last / 2); father > first - 1; father -= 1) {
            
            // Fixes the heap
            fix_heap(A, father, last);
        }
    }

    // This function calls the various functions defined in this file and runs the heap sort
    void heap_sort(uint32_t *A, uint32_t n) {

        // Define the arguments
        uint32_t first = 1;
        uint32_t last = n;
        uint32_t leaf;
        uint32_t copy;

        // Builds the heap using the values in array A
        build_heap(A, first, last);

        // Goes through all values in array A and sorts them in order
        for (leaf = last; leaf > first; leaf -= 1) {
            // Swaps the values of first and leaf
            copy = A[first - 1];
            A[first - 1] = A[leaf - 1];
            A[leaf - 1] = copy;
            fix_heap(A, first, leaf - 1);
        }
    }


}

bool dequeue(PriorityQueue *q, Node **n) {

}

void pq_print(PriorityQueue *q) {

}

