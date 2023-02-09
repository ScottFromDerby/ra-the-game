#pragma once
#include <stdbool.h>

//  Player progress

struct PlayerProgress
{
    bool bHasVisitedOtherScreens;
};

void init_progress();

extern struct PlayerProgress g_Progress;
