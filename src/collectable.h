#pragma once
#include "wasm4.h"

enum
{
    MAX_COLLECTABLES = 8
};

enum CollectableType
{
    COLL_Heart,
    COLL_Coin,
};

struct Collectable
{
    enum CollectableType type;
    int xPos;
    int yPos;
    int ticksLeft;
};
extern struct Collectable g_collectables[MAX_COLLECTABLES];

void clear_collectables();
void add_collectable(enum CollectableType type, int x, int y, int ticks);
void tick_collectables();
void draw_collectables();