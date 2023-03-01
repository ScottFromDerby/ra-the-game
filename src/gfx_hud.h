#pragma once

// SPRITE_Hud
#define SPRITE_HudWidth 64
#define SPRITE_HudHeight 64
#define SPRITE_HudFlags BLIT_2BPP
extern const uint8_t SPRITE_Hud[1024];

static void blitHalfTile_SPRITE_Hud(int32_t x, int32_t y, uint32_t tileX, uint32_t tileY, uint32_t flags)
{
    blitSub(SPRITE_Hud, HALFTILE * x, HALFTILE * y, HALFTILE, HALFTILE, HALFTILE * tileX, HALFTILE * tileY, SPRITE_HudWidth, SPRITE_HudFlags | flags);
}

static void blitTile_SPRITE_Hud(int32_t x, int32_t y, uint32_t tileX, uint32_t tileY, uint32_t flags)
{
    blitSub(SPRITE_Hud, TILESIZE * x, TILESIZE * y, TILESIZE, TILESIZE, TILESIZE * tileX, TILESIZE * tileY, SPRITE_HudWidth, SPRITE_HudFlags | flags);
}

