#include "progress.h"

struct PlayerProgress g_Progress;

void init_progress()
{
    g_Progress.bHasVisitedOtherScreens = false;
}