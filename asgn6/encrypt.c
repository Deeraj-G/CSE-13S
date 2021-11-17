#include <gmp.h>
#include <inttypes.h>
#include <stdio.h>
#include "randstate.h"
#include "numtheory.h"

int main() {
    mpz_t n;
    mpz_init(n);
    gmp_scanf("%Zd", n);

    uint64_t iters = 10;
    uint64_t seed = 2021;
    randstate_init(seed);

    if (is_prime(n, iters) == true) {
        printf("is prime\n");
    } else {
        printf("not prime\n");
    }

    mpz_clear(n);
}
