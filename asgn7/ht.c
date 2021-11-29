#include "bst.h"
#include "ht.h"
#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <stdlib.h>


struct HashTable {
    uint64_t salt [2];
    uint32_t size ;
    Node ** trees ;
};
