#pragma once
#include "wasm4.h"

void draw_player_sprite();
void draw_weapon();
void tick_weapon();
void start_swing_sword();

enum SwordSwingState
{
    Swing_Off,
    Swing_Side,
    Swing_Diagonal,
    Swing_Forwards,
};
extern enum SwordSwingState g_swordSwingState;
extern u8 g_swordSwingTicks;