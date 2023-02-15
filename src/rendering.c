#include "rendering.h"
#include "gfx_animtiles.h"
#include "gfx_overworld.h"
#include "main.h"

void get_tile_from_point(u8 x, u8 y, u8 *xTile, u8 *yTile)
{
    *xTile = x / TILESIZE;
    *yTile = y / TILESIZE;
}

MetaTile get_meta_tile(uint8_t x, uint8_t y)
{
    if (x >= NUM_TILES_WIDTH || y >= NUM_TILES_HEIGHT)
    {
        return Empt;
    }
    return g_currentScreen->screen_metatiles[x + y * NUM_TILES_WIDTH];
}

MetaTile get_meta_tile_transition(uint8_t x, uint8_t y)
{
    return g_transitionFromScreen->screen_metatiles[x + y * 10];
}

MetaTile get_metatile_at_point(u8 x, u8 y)
{
    if (x >= SCREEN_WIDTH || y >= SCREEN_HEIGHT)
    {
        return Empt;
    }
    return get_meta_tile(x / TILESIZE, y / TILESIZE);
}

void get_tile_infront_of_player(u8* xTileOut, u8* yTileOut)
{
    get_tile_from_point(g_playerX, g_playerY, xTileOut, yTileOut);
    switch (g_currentFacing)
    {
        case Up:
            if ((*yTileOut) > 0)
            {
                (*yTileOut)--;
            }
            return;
        case Down:
            if ((*yTileOut) < NUM_TILES_HEIGHT)
            {
                (*yTileOut)++;
            }
            return;
        case Left:
            if ((*xTileOut) > 0)
            {
                (*xTileOut)--;
            }
            return;
        case Right:
            if ((*xTileOut) < NUM_TILES_WIDTH)
            {
                (*xTileOut)++;
            }
            return;
    }
}

void draw_animtile(int x, int y, u32 tile, u32 flags, int xOffs, int yOffs)
{
    blitSub(SPRITE_AnimTiles, HALFTILE * x + xOffs, HALFTILE * y + yOffs, HALFTILE, HALFTILE, (tile % 0x04) * HALFTILE, (tile / 0x04) * HALFTILE, SPRITE_AnimTilesWidth, SPRITE_AnimTilesFlags | flags);
}

void draw_halftile(int x, int y, u32 tile, u32 flags, int xOffs, int yOffs)
{
    blitSub(SPRITE_Overworld, HALFTILE * x + xOffs, HALFTILE * y + yOffs, HALFTILE, HALFTILE, (tile % 0x10) * HALFTILE, (tile / 0x10) * HALFTILE, SPRITE_OverworldWidth, SPRITE_OverworldFlags | flags);
}

void draw_metatile(int x, int y, MetaTile tile, u32 flags, int xOffs, int yOffs)
{
    uint8_t TL = 0;
    uint8_t TR = 0;
    uint8_t BL = 0;
    uint8_t BR = 0;
    u32 tile_flags = get_meta_tile_info(tile, &TL, &TR, &BL, &BR);
    draw_halftile(x * 2, y * 2, (u32)TL, tile_flags | flags, xOffs, yOffs);
    draw_halftile(x * 2 + 1, y * 2, (u32)TR, tile_flags | flags, xOffs, yOffs);
    draw_halftile(x * 2, y * 2 + 1, (u32)BL, tile_flags | flags, xOffs, yOffs);
    draw_halftile(x * 2 + 1, y * 2 + 1, (u32)BR, tile_flags | flags, xOffs, yOffs);
}
