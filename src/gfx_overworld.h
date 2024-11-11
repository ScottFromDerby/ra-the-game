#pragma once

// SPRITE_Overworld
#define SPRITE_OverworldWidth 128
#define SPRITE_OverworldHeight 288
#define SPRITE_OverworldFlags BLIT_2BPP
extern const uint8_t SPRITE_Overworld[9216];

static void blitHalfTileOffs_SPRITE_Overworld(int32_t x, int32_t y, int32_t xOffs, int32_t yOffs, uint32_t tileX, uint32_t tileY, uint32_t flags)
{
    blitSub(SPRITE_Overworld, (HALFTILE * x) + xOffs, (HALFTILE * y) + yOffs, HALFTILE, HALFTILE, HALFTILE * tileX, HALFTILE * tileY, SPRITE_OverworldWidth, SPRITE_OverworldFlags | flags);
}

static void blitHalfTile_SPRITE_Overworld(int32_t x, int32_t y, uint32_t tileX, uint32_t tileY, uint32_t flags)
{
    blitSub(SPRITE_Overworld, HALFTILE * x, HALFTILE * y, HALFTILE, HALFTILE, HALFTILE * tileX, HALFTILE * tileY, SPRITE_OverworldWidth, SPRITE_OverworldFlags | flags);
}

static void blitTile_SPRITE_Overworld(int32_t x, int32_t y, uint32_t tileX, uint32_t tileY, uint32_t flags)
{
    blitSub(SPRITE_Overworld, TILESIZE * x, TILESIZE * y, TILESIZE, TILESIZE, TILESIZE * tileX, TILESIZE * tileY, SPRITE_OverworldWidth, SPRITE_OverworldFlags | flags);
}

