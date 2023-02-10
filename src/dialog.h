#pragma once
#include "wasm4.h"

void show_dialog(const char* line1, const char* line2, const char* line3);

void close_dialog();

extern bool g_bShowingDialogBG;
extern char g_dialogContentLine1[64];
extern char g_dialogContentLine2[64];
extern char g_dialogContentLine3[64];