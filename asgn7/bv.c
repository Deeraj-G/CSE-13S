#include "bv.h"
#include <stdbool.h>
#include <stdint.h>
#include <inttypes.h>
#include <stdlib.h>

struct BitVector {
    uint32_t length ;
    uint8_t * vector ;
};
