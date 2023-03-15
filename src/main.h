#pragma once

extern u8 g_playerX;
extern u8 g_playerY;
extern u8 g_currentWorldX;
extern u8 g_currentWorldY;

extern u8 g_damagePushX;
extern u8 g_damagePushY;
extern u8 g_damageFramesLeft;

extern u8 g_upHeldFrames;
extern u8 g_downHeldFrames;
extern u8 g_leftHeldFrames;
extern u8 g_rightHeldFrames;

extern int g_transitionFramesLeft;
extern enum Direction g_transitionDirection;

enum Direction
{
    Left,
    Right,
    Up,
    Down,
};

extern enum Direction g_currentFacing;

enum GameState
{
    INGAME,
    PAUSE,
    GAMEOVER
};
extern enum GameState g_gameState;

extern struct ScreenMeta g_currentScreen;
extern struct ScreenMeta g_transitionFromScreen;

void set_screen(u8 x, u8 y, bool bForce);