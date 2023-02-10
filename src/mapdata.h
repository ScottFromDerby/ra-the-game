#pragma once

#include "wasm4.h"

enum MetaTileLookup
{
    Empt,
    IWal,   //  Empty but blocking
    Gras,
    Gra2,   //  Grass backwards
    Bush,
    Path,
    HsWn,   //  House window
    HsDr,   //  House door
    RfTL,   //  Roof TL
    RfTC,   //  Roof TC
    RfTR,   //  Roof TR
    RfBL,   //  Roof BL
    RfBC,   //  Roof BC
    RfBR,   //  Roof BR
    Tre1,   //  Tree TL
    Tre2,   //  Tree TR
    Tre3,   //  Tree BL
    Tre4,   //  Tree BR
    Kenl,   //  Kennel
    Fenc,   //  Double Fence
};

typedef uint8_t MetaTile;

struct ScreenMeta
{
    MetaTile screen_metatiles[9*10];
};

extern struct ScreenMeta TestScreenMeta;

struct WorldMap
{
    enum
    {
        WORLD_MAX_X = 4,
        WORLD_MAX_Y = 4,
        START_WORLD_X = 2,
        START_WORLD_Y = 2,
    };

    struct ScreenMeta* World[WORLD_MAX_X*WORLD_MAX_Y];
};

extern struct WorldMap MainWorldMap;

struct ScreenMeta* get_screen(uint8_t x, uint8_t y);

uint32_t get_meta_tile_info(MetaTile metaTile, uint8_t* TL, uint8_t* TR, uint8_t* BL, uint8_t* BR);

bool can_move_onto_tile(MetaTile metaTile);