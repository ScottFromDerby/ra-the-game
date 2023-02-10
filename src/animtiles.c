#include "animtiles.h"
#include "wasm4.h"

struct AnimatedTile g_AnimTiles[NUM_ANIM_TILES];

void tick_animated_tile(struct AnimatedTile *tile)
{
    tile->ticks++;
    switch (tile->type)
    {
    case ATT_None:
        break;
    case ATT_Flower:
        if (tile->ticks == 21)
        {
            tile->ticks = 0;
            tile->phase = (tile->phase + 1) % 4;
        }
        break;
    }
}

void add_anim_tile(enum AnimatedTileType tile, u8 x, u8 y, u8 startPhase)
{
    for (int i = 0; i < NUM_ANIM_TILES; ++i)
    {
        if (g_AnimTiles[i].type == ATT_None)
        {
            g_AnimTiles[i].type = tile;
            g_AnimTiles[i].phase = startPhase;
            g_AnimTiles[i].ticks = 0;
            g_AnimTiles[i].xPos = x;
            g_AnimTiles[i].yPos = y;
            return;
        }
    }
    trace("Couldn't add animated tile?!");
}

void tick_animated_tiles()
{
    for (int i = 0; i < NUM_ANIM_TILES; ++i)
    {
        if (g_AnimTiles[i].type != ATT_None)
        {
            tick_animated_tile(&g_AnimTiles[i]);
        }
    }
}