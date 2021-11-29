#include "bv.h"
#include "bf.h"
#include "salts.h"
#include <stdbool.h>
#include <stdint.h>
#include <inttypes.h>
#include <stdlib.h>

struct BloomFilter {
    uint64_t primary [2]; // Primary hash function salt .
    uint64_t secondary [2]; // Secondary hash function salt .
    uint64_t tertiary [2]; // Tertiary hash function salt .
    BitVector * filter ;
};

BloomFilter *bf_create(uint32_t size) {
    BloomFilter *bf = (BloomFilter *) malloc(sizeof(BloomFilter));

    bf->primary[0] = SALT_PRIMARY_LO;
    bf->primary[1] = SALT_PRIMARY_HI;
    bf->secondary[0] = SALT_SECONDARY_LO;
    bf->secondary[1] = SALT_SECONDARY_HI;
    bf->tertiary[0] = SALT_HASHTABLE_LO;
    bf->tertiary[1] = SALT_HASHTABLE_HI;
}
