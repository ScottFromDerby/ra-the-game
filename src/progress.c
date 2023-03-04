#include "progress.h"
#include "main.h"
#include "player.h"

struct PlayerProgress g_Progress;

void init_progress()
{
    g_Progress.bHasVisitedOtherScreens = false;
    g_Progress.musicBoxState = 0;
}

void reset_game()
{
    struct SaveData savefile;
    savefile.saveIsActive = 1;
    savefile.playerX = 100;
    savefile.playerY = 100;
    savefile.worldX = 2;
    savefile.worldY = 2;
    savefile.coins = 69;
    savefile.hearts = 12;
    savefile.maxHearts = 24;
    
    for (int i = 0; i < WORLD_MAX_X * WORLD_MAX_Y; ++i)
    {
        savefile.progress.visited[i] = false;
    }
    diskw(&savefile, sizeof(savefile));

    start();    //  Will then loadgame
}

void load_game()
{
    struct SaveData savefile;
    uint32_t read = diskr(&savefile, sizeof(savefile));
    tracef("loading save: %d: %d %d %d %d %d", read, savefile.saveIsActive, savefile.playerX, savefile.playerY, savefile.worldX, savefile.worldY);
    if (savefile.saveIsActive)
    {
        g_playerX = savefile.playerX;
        g_playerY = savefile.playerY;
        g_Progress = savefile.progress;
        g_playerNumHalfHearts = savefile.hearts;
        g_playerMaxNumHalfHearts = savefile.maxHearts;
        g_playerNumCoins = savefile.coins;
        set_screen(savefile.worldX, savefile.worldY, true);
    }
}

void save_game()
{
    struct SaveData savefile;
    savefile.saveIsActive = 1;
    savefile.playerX = g_playerX;
    savefile.playerY = g_playerY;
    savefile.worldX = g_currentWorldX;
    savefile.worldY = g_currentWorldY;
    savefile.progress = g_Progress;
    savefile.hearts = g_playerNumHalfHearts;
    savefile.maxHearts = g_playerMaxNumHalfHearts;
    savefile.coins = g_playerNumCoins;
    diskw(&savefile, sizeof(savefile));
}