#include "progress.h"
#include "main.h"

struct PlayerProgress g_Progress;

void init_progress()
{
    g_Progress.bHasVisitedOtherScreens = false;
}

void reset_game()
{
    struct SaveData savefile;
    savefile.saveIsActive = 1;
    savefile.playerX = 100;
    savefile.playerY = 100;
    savefile.worldX = 2;
    savefile.worldY = 2;
    diskw(&savefile, sizeof(savefile));
    start();
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
    diskw(&savefile, sizeof(savefile));
}