#pragma once

// SPRITE_Weapon
#define SPRITE_WeaponWidth 64
#define SPRITE_WeaponHeight 32
#define SPRITE_WeaponFlags BLIT_2BPP
extern const uint8_t SPRITE_Weapon[512];

static void blitHalfTile_SPRITE_Weapon(int32_t x, int32_t y, uint32_t tileX, uint32_t tileY, uint32_t flags)
{
    blitSub(SPRITE_Weapon, HALFTILE * x, HALFTILE * y, HALFTILE, HALFTILE, HALFTILE * tileX, HALFTILE * tileY, SPRITE_WeaponWidth, SPRITE_WeaponFlags | flags);
}

static void blitTile_SPRITE_Weapon(int32_t x, int32_t y, uint32_t tileX, uint32_t tileY, uint32_t flags)
{
    blitSub(SPRITE_Weapon, TILESIZE * x, TILESIZE * y, TILESIZE, TILESIZE, TILESIZE * tileX, TILESIZE * tileY, SPRITE_WeaponWidth, SPRITE_WeaponFlags | flags);
}

