#pragma once

#include <stdlib.h>
#include <stdint.h>
#include <math.h>

#define max(a, b) (a > b ? a : b)
#define ZERO (uint128_t){{0, 0, 0, 0}}
#define ONE (uint128_t){{1, 0, 0, 0}}
#define TWO (uint128_t){{2, 0, 0, 0}}
#define THREE (uint128_t){{3, 0, 0, 0}}

typedef struct {
    uint32_t bits[4];
} uint128_t;

uint128_t from64(uint64_t num);
uint128_t mul(uint128_t num1, uint128_t num2);
uint128_t add(uint128_t num1, uint128_t num2);
uint128_t divby64(uint128_t num, uint64_t m);
uint128_t sub(uint128_t num1, uint128_t num2);
int cmp(uint128_t a, uint128_t b);