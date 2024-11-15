#pragma once
#include "wasm4.h"
#include "mapdata.h"

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
    bool visited[WORLD_MAX_X*WORLD_MAX_Y];
};

void init_progress();

struct SaveData
{
    u8 saveIsActive;
    u8 worldX;
    u8 worldY;
    int playerX;
    int playerY;
    
    int coins;
    int hearts;
    int maxHearts;

    struct PlayerProgress progress;
};

extern struct PlayerProgress g_Progress;

void reset_game();
void load_game();
void save_game();