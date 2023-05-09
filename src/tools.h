#pragma once

#include "wasm4.h"

void tostr(char* buffer, int value);
char* tostrdirty(int value);

static int clamp(int val, int lower, int upper)
{
    return (val < lower) ? lower : (val > upper) ? upper
                                                 : val;
}

static float clampf(float val, float lower, float upper)
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

static float maxf(float a, float b)
{
    return a > b ? a : b;
}

static int min(int a, int b)
{
    return a < b ? a : b;
}

static float minf(float a, float b)
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
 
static int strlen(char* str)
{
    int len = 0;
    while(*str != '\0')
    {
        len++;
        str++;
    }
    return len;
}
static void* memset(void* s, int c, unsigned int len)
{
    unsigned char* p = s;
    while(len--)
    {
        *p++ = (unsigned char)c;
    }
    return s;
}

static void memcpy(void* dest, void* src, int n)
{ 
    // Typecast src and dest addresses to (char *) 
    char* csrc = (char*)src; 
    char* cdest = (char*)dest; 
  
    // Copy contents of src[] to dest[]
    for (int i = 0; i < n; i++)
    {
        cdest[i] = csrc[i];
    }
} 

static bool rc_intersect(int x1, int w1, int y1, int h1, int x2, int w2, int y2, int h2)
{
    return !(x1 > x2+w2 || x1+w1 < x2 || y1 > y2+h2 || y1+h1 < y2);
}

static bool rc_intersect2(struct Rect* rc1, struct Rect* rc2)
{
    return !(rc1->x > rc2->x+rc2->w || rc1->x+rc1->w < rc2->x || rc1->y > rc2->y+rc2->h || rc1->y+rc1->h < rc2->y);
}

