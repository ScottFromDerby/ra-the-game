#pragma once

//  Calculate length of input char/str. Used in order to right-align
void gfx_charlenpx(char which, u32* offset, u32* offsetSize);
u32 gfx_strlenpx(const char* str);

//  Normal draw stuff
u32 gfx_drawchar(char which, int x, int y, u16 drawcolors);
void gfx_drawstr(const char* str, int x, int y, u16 drawcolors, bool rightalign);
void gfx_drawstrn(const char *str, int x, int y, u16 drawcolors, bool rightalign, int numChars);

//  Helper for drawing a single value
void gfx_drawval(int val, int x, int y, u16 drawcolors);
void gfx_drawval_rightalign(int val, int x, int y, u16 drawcolors);

void gfx_setpixel(int x, int y, int paletteColor);

void gfx_debughighlightpixel(int x, int y);
void gfx_drawdebugpixels();