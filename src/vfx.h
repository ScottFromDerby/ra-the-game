#pragma once
#include "wasm4.h"

enum
{
    MAX_VFX_SPRITES = 16
};

enum VFXType
{
    VFX_LeafFoliage,
};

struct VFXSprite
{
    enum VFXType type;
    int x_10;   //  must be divided by 10 for screenspace
    int y_10;   //  must be divided by 10 for screenspace
    int xVel;
    int yVel;
    int ticksLeft;
    int rng;
    u32 flags;
};

extern struct VFXSprite g_vfx[MAX_VFX_SPRITES];

extern void clear_vfx();
extern void add_vfx(enum VFXType type, int x, int y, int xVel, int yVel, int ticks, u32 flags);
extern void tick_vfx();
extern void draw_vfx();
