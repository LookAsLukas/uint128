#include "int128.h"
#include <stdio.h>

const uint128_t uint128_0 = {{0, 0, 0, 0}};
const uint128_t uint128_1 = {{1, 0, 0, 0}};
const uint128_t uint128_2 = {{2, 0, 0, 0}};
const uint128_t uint128_3 = {{3, 0, 0, 0}};
const uint128_t uint128_max = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF}};

uint128_t uint128_from_u64(uint64_t num) {
    return (uint128_t){{(uint32_t)(num & 0xFFFFFFFF), (uint32_t)(num >> 32), 0, 0}};
}

uint64_t uint128_to_u64(uint128_t num) {
    return ((uint64_t)num.bits[1] << 32) | num.bits[0];
}

uint128_t uint128_add(uint128_t a, uint128_t b) {
    uint128_t result = uint128_0;
    uint64_t carry = 0;
    
    for (int i = 0; i < 4; i++) {
        uint64_t sum = (uint64_t)a.bits[i] + b.bits[i] + carry;
        result.bits[i] = (uint32_t)(sum & 0xFFFFFFFF);
        carry = sum >> 32;
    }
    
    return result;
}

uint128_t uint128_sub(uint128_t a, uint128_t b) {
    uint128_t result = uint128_0;
    uint64_t borrow = 0;
    
    for (int i = 0; i < 4; i++) {
        uint64_t diff = (uint64_t)a.bits[i] - b.bits[i] - borrow;
        result.bits[i] = (uint32_t)(diff & 0xFFFFFFFF);
        borrow = (diff >> 32) ? 1 : 0;
    }
    
    return result;
}

uint128_t uint128_mul(uint128_t a, uint128_t b) {
    uint128_t result = uint128_0;
    uint64_t carry;
    
    for (int i = 0; i < 4; i++) {
        carry = 0;
        for (int j = 0; j < 4; j++) {
            if (i + j >= 4) continue;
            
            uint64_t product = (uint64_t)a.bits[i] * b.bits[j];
            uint64_t sum = product + result.bits[i+j] + carry;
            
            result.bits[i+j] = (uint32_t)(sum & 0xFFFFFFFF);
            carry = sum >> 32;
        }
    }
    
    return result;
}

int uint128_cmp(uint128_t a, uint128_t b) {
    for (int i = 3; i >= 0; i--) {
        if (a.bits[i] < b.bits[i]) return -1;
        if (a.bits[i] > b.bits[i]) return 1;
    }
    return 0;
}

bool uint128_eq(uint128_t a, uint128_t b) {
    return uint128_cmp(a, b) == 0;
}

bool uint128_lt(uint128_t a, uint128_t b) {
    return uint128_cmp(a, b) < 0;
}

bool uint128_gt(uint128_t a, uint128_t b) {
    return uint128_cmp(a, b) > 0;
}

uint128_t uint128_div_u64(uint128_t a, uint64_t b) {
    if (b == 0) {
        // Handle division by zero (return max value)
        return uint128_max;
    }
    
    uint128_t result = uint128_0;
    uint64_t remainder = 0;
    
    for (int i = 3; i >= 0; i--) {
        uint64_t dividend = ((uint64_t)remainder << 32) | a.bits[i];
        result.bits[i] = (uint32_t)(dividend / b);
        remainder = dividend % b;
    }
    
    return result;
}

void uint128_print(uint128_t num) {
    printf("0x%08x%08x%08x%08x\n", num.bits[3], num.bits[2], num.bits[1], num.bits[0]);
}