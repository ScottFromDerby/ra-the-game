#pragma once
#include "wasm4.h"
#include "mapdata.h"

void get_tile_centerpoint(int xTile, int yTile, int* x, int* y);
void get_tile_from_point(int x, int y, u8 *xTile, u8 *yTile);
MetaTile get_meta_tile(uint8_t x, uint8_t y);
MetaTile get_meta_tile_transition(uint8_t x, uint8_t y);
MetaTile get_metatile_at_point(u8 x, u8 y);
void get_tile_infront_of_player(u8* xTileOut, u8* yTileOut);
void draw_animtile(int x, int y, u32 tile, u32 flags, int xOffs, int yOffs);
void draw_halftile(int x, int y, u32 tile, u32 flags, int xOffs, int yOffs);
void draw_metatile(int x, int y, MetaTile tile, u32 flags, int xOffs, int yOffs);