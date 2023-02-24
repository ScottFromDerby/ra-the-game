#pragma once
#include "wasm4.h"

//  Player progress

enum
{
    NUM_INVENTORY_ITEMS = 16
};

enum InventoryItemType
{
    None,
    Shield,
    Sword,
    Book,
    Gameboy,
};

struct PlayerProgress
{
    //  NB. merge into savedata?
    bool bHasVisitedOtherScreens;
    u8 musicBoxState;
    enum InventoryItemType inventoryItems[NUM_INVENTORY_ITEMS];
};

void init_progress();

struct SaveData
{
    u8 saveIsActive;
    u8 worldX;
    u8 worldY;
    u8 playerX;
    u8 playerY;
    struct PlayerProgress progress;
};

extern struct PlayerProgress g_Progress;

void reset_game();
void load_game();
void save_game();