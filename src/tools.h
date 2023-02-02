#pragma once
#include <stdint.h>

void tostr(char *buffer, u32 value);
char *tostrdirty(u32 value);

static int clamp(int val, int lower, int upper)
{
    return (val < lower) ? lower : (val > upper) ? upper
                                                 : val;
}

static u8 rand()
{
    static u32 rand_state = 777;
    rand_state = rand_state * 1664525 + 1013904223;
    return rand_state >> 24;
}

static int abs(int v)
{
    return v >= 0 ? v : -v;
}

static int max(int a, int b)
{
    return a > b ? a : b;
}

static int min(int a, int b)
{
    return a < b ? a : b;
}
