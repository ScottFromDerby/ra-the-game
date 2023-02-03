#include "wasm4.h"
#include "gfx.h"
#include "tools.h"

#include "gfx_font.h"

//	NB. One larger!				A  B  C   D   E   F   G   H   I   J   K   L   M   N   O   P   Q   R   S   T   U   V   W   X   Y    Z    a    b    c    d    e    f    g    h    i    j    k    l    m    n    o    p    q    r    s    t    u    v    w    x    y    z    0    1    2    3    4    5    6    7    8    9    .    ,    !
const u32 FONT_6pxOffsets[] = {0, 4, 8, 12, 16, 20, 24, 28, 32, 34, 38, 42, 45, 51, 56, 60, 64, 68, 72, 76, 80, 84, 88, 94, 98, 102, 106, 110, 114, 118, 122, 126, 130, 134, 138, 140, 143, 147, 150, 156, 160, 164, 168, 172, 176, 180, 183, 187, 191, 197, 201, 205, 209, 213, 217, 221, 225, 229, 233, 237, 241, 245, 249, 251, 254, 256};

void gfx_charlenpx(char which, u32 *offset, u32 *offsetSize)
{
	if (which >= 'A' && which <= 'Z')
	{
		*offset = FONT_6pxOffsets[which - 'A'];
		*offsetSize = FONT_6pxOffsets[which - 'A' + 1] - *offset;
	}
	else if (which >= 'a' && which <= 'z')
	{
		*offset = FONT_6pxOffsets[which - 'a' + 26];
		*offsetSize = FONT_6pxOffsets[which - 'a' + 26 + 1] - *offset;
	}
	else if (which >= '0' && which <= '9')
	{
		*offset = FONT_6pxOffsets[which - '0' + 26 + 26];
		*offsetSize = FONT_6pxOffsets[which - '0' + 26 + 26 + 1] - *offset;
	}
	else if (which == '.')
	{
		*offset = FONT_6pxOffsets[26 + 26 + 10 + 0];
		*offsetSize = FONT_6pxOffsets[26 + 26 + 10 + 0 + 1] - *offset;
	}
	else if (which == ',')
	{
		*offset = FONT_6pxOffsets[26 + 26 + 10 + 1];
		*offsetSize = FONT_6pxOffsets[26 + 26 + 10 + 1 + 1] - *offset;
	}
	else if (which == '!')
	{
		*offset = FONT_6pxOffsets[26 + 26 + 10 + 2];
		*offsetSize = FONT_6pxOffsets[26 + 26 + 10 + 1 + 2] - *offset;
	}
	else if (which == ' ')
	{
		*offset = 0;
		*offsetSize = 2;
	}
	else
	{
		*offset = 0;
		*offsetSize = 0;
		trace("Unknown drawchar!");
	}
}

u32 gfx_strlenpx(const char *str)
{
	u32 width = 0;
	while (*str != '\0')
	{
		u32 offset;
		u32 offsetSize;
		gfx_charlenpx(*str, &offset, &offsetSize);
		width += offsetSize;
		str++;
	}
	return width;
}

//	Returns width of char drawn
u32 gfx_drawchar(char which, int x, int y, u16 drawcolors)
{
	u32 offset = 0;
	u32 offsetSize = 0;

	if (which == ' ')
	{
		return 2;
	}

	gfx_charlenpx(which, &offset, &offsetSize);

	*DRAW_COLORS = drawcolors;
	blitSub(FONT_6px, x, y, offsetSize, FONT_6pxHeight, offset, 0, FONT_6pxWidth, FONT_6pxFlags);
	return offsetSize;
}

void gfx_drawstr(const char *str, int x, int y, u16 drawcolors, bool rightalign)
{
	if (rightalign)
	{
		x -= gfx_strlenpx(str);
	}

	while (*str != '\0')
	{
		x += gfx_drawchar(*str, x, y, drawcolors);
		str++;
	}
}

void gfx_drawval(int val, int x, int y, u16 drawcolors)
{
	char buffer[256];
	tostr(buffer, val);
	gfx_drawstr(buffer, x, y, drawcolors, false);
}

void gfx_drawval_rightalign(int val, int x, int y, u16 drawcolors)
{
	char buffer[256];
	tostr(buffer, val);
	gfx_drawstr(buffer, x, y, drawcolors, true);
}

void gfx_setpixel(int x, int y, int paletteColor)
{
	if (x > SCREEN_SIZE || y > SCREEN_SIZE)
	{
		return;
	}

	// uint8_t& pixel = FRAMEBUFFER[y*40 + x / 4];

	// The byte index into the framebuffer that contains (x, y)
	int idx = (y * 160 + x) >> 2;

	// Calculate the bits within the byte that corresponds to our position
	int shift = (x & 0b11) << 1;
	int mask = 0b11 << shift;

	int color = paletteColor;

	// Write to the framebuffer
	FRAMEBUFFER[idx] = (u8)((color << shift) | (FRAMEBUFFER[idx] & ~mask));
}