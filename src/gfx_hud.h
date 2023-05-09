#pragma once

// SPRITE_Hud
#define SPRITE_HudWidth 64
#define SPRITE_HudHeight 80
#define SPRITE_HudFlags BLIT_2BPP
extern const uint8_t SPRITE_Hud[1280];

static void blitHalfTileOffs_SPRITE_Hud(int32_t x, int32_t y, int32_t xOffs, int32_t yOffs, uint32_t tileX, uint32_t tileY, uint32_t flags)
{
    blitSub(SPRITE_Hud, (HALFTILE * x) + xOffs, (HALFTILE * y) + yOffs, HALFTILE, HALFTILE, HALFTILE * tileX, HALFTILE * tileY, SPRITE_HudWidth, SPRITE_HudFlags | flags);
}

static void blitHalfTile_SPRITE_Hud(int32_t x, int32_t y, uint32_t tileX, uint32_t tileY, uint32_t flags)
{
    blitSub(SPRITE_Hud, HALFTILE * x, HALFTILE * y, HALFTILE, HALFTILE, HALFTILE * tileX, HALFTILE * tileY, SPRITE_HudWidth, SPRITE_HudFlags | flags);
}

static void blitTile_SPRITE_Hud(int32_t x, int32_t y, uint32_t tileX, uint32_t tileY, uint32_t flags)
{
    blitSub(SPRITE_Hud, TILESIZE * x, TILESIZE * y, TILESIZE, TILESIZE, TILESIZE * tileX, TILESIZE * tileY, SPRITE_HudWidth, SPRITE_HudFlags | flags);
}

