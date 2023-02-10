#pragma once

#include "wasm4.h"

void tostr(char* buffer, int value);
char* tostrdirty(int value);

static int clamp(int val, int lower, int upper)
{
    return (val < lower) ? lower : (val > upper) ? upper
                                                 : val;
}

static u8 clampu8(u8 val, u8 lower, u8 upper)
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

static int rand_range(int lower, int upper)
{
    return (((int)rand() % (upper - lower)) + lower);
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

static char* strcpy(char* destination, const char* source)
{
    // return if no memory is allocated to the destination
    if (destination == NULL)
    {
        return NULL;
    }
 
    // take a pointer pointing to the beginning of the destination string
    char *ptr = destination;
 
    // copy the C-string pointed by source into the array
    // pointed by destination
    while (*source != '\0')
    {
        *destination = *source;
        destination++;
        source++;
    }
 
    // include the terminating null character
    *destination = '\0';
 
    // the destination is returned by standard `strcpy()`
    return ptr;
}
 