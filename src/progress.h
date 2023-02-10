#pragma once
#include "wasm4.h"

//  Player progress

struct PlayerProgress
{
    bool bHasVisitedOtherScreens;
};

void init_progress();

extern struct PlayerProgress g_Progress;
