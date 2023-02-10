#pragma once

#include "wasm4.h"

enum
{
    NUM_ANIM_TILES = 16
};

enum AnimatedTileType
{
    ATT_None,
    ATT_Flower,
};

struct AnimatedTile
{
    enum AnimatedTileType type;
    u8 xPos;
    u8 yPos;
    u8 ticks;
    u8 phase;
    u32 flags;
};
extern struct AnimatedTile g_AnimTiles[NUM_ANIM_TILES];

void add_anim_tile(enum AnimatedTileType tile, u8 x, u8 y, u8 startPhase);
void tick_animated_tile(struct AnimatedTile *tile);
void tick_animated_tiles();