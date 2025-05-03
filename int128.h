#pragma once

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

typedef struct {
    uint32_t bits[4];  // Little-endian: bits[0] is least significant
} uint128_t;

// Constants
extern const uint128_t uint128_0;
extern const uint128_t uint128_1;
extern const uint128_t uint128_2;
extern const uint128_t uint128_3;
extern const uint128_t uint128_max;

// Conversion
uint128_t uint128_from_u64(uint64_t num);
uint64_t uint128_to_u64(uint128_t num);

// Arithmetic
uint128_t uint128_add(uint128_t a, uint128_t b);
uint128_t uint128_sub(uint128_t a, uint128_t b);
uint128_t uint128_mul(uint128_t a, uint128_t b);
uint128_t uint128_div(uint128_t a, uint128_t b);
uint128_t uint128_div_u64(uint128_t a, uint64_t b);

// Comparison
int uint128_cmp(uint128_t a, uint128_t b);
bool uint128_eq(uint128_t a, uint128_t b);
bool uint128_lt(uint128_t a, uint128_t b);
bool uint128_gt(uint128_t a, uint128_t b);

// Utility
void uint128_print(uint128_t num);