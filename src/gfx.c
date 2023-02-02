#include "wasm4.h"
#include "gfx.h"
#include "tools.h"

// FONT_6px
#define FONT_6pxWidth 256      
#define FONT_6pxHeight 6       
#define FONT_6pxFlags BLIT_1BPP
const u8 FONT_6px[192] = { 0x4c,0x4c,0x66,0x6a,0x8a,0xa2,0x92,0x4c,0x4c,0x6e,0xaa,0xaa,0xab,0x82,0x00,0x80,0x82,0x25,0x10,0x00,0x00,0x00,0x08,0x00,0x00,0x00,0x22,0x26,0x17,0x37,0x22,0x02,0xaa,0xaa,0x88,0x8a,0x8a,0xa5,0x5a,0xaa,0xaa,0x84,0xaa,0xaa,0xa8,0x93,0x11,0x91,0x1b,0x01,0x53,0x4c,0x44,0x44,0x6d,0x55,0x55,0x57,0x56,0x51,0x54,0x41,0x55,0x02,0xac,0x8a,0xcc,0xae,0x8b,0x25,0x56,0xaa,0xaa,0x44,0xaa,0xa9,0x29,0x2a,0xaa,0xab,0xaa,0xa5,0x92,0xaa,0xaa,0xaa,0x89,0x55,0x52,0x51,0x72,0x12,0x56,0x62,0x23,0x02,0xea,0x8a,0x88,0xaa,0xaa,0xa5,0x52,0xac,0xac,0x24,0xaa,0xaa,0x92,0x2a,0xa2,0xb1,0x2a,0xa5,0x52,0xaa,0xaa,0xa8,0x29,0x55,0x52,0x54,0x52,0x41,0x71,0x52,0x51,0x00,0xac,0x6c,0x68,0x6a,0x92,0xb5,0x52,0x48,0x6a,0xc4,0x64,0x52,0x93,0x9b,0x19,0x99,0x0a,0xa5,0x4a,0xaa,0x4c,0x68,0xc4,0xc8,0xa5,0x17,0x27,0x76,0x16,0x22,0x26,0x4a,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x30,0x08,0x00,0x00,0x08,0x20,0x00,0x00,0x00,0x60,0x00,0x00,0x00,0x00,0x00,0x10 };

//	NB. One larger!				A  B  C   D   E   F   G   H   I   J   K   L   M   N   O   P   Q   R   S   T   U   V   W   X   Y    Z    a    b    c    d    e    f    g    h    i    j    k    l    m    n    o    p    q    r    s    t    u    v    w    x    y    z    0    1    2    3    4    5    6    7    8    9    .    ,    !
const u32 FONT_6pxOffsets[] = { 0, 4, 8, 12, 16, 20, 24, 28, 32, 34, 38, 42, 45, 51, 56, 60, 64, 68, 72, 76, 80, 84, 88, 94, 98, 102, 106, 110, 114, 118, 122, 126, 130, 134, 138, 140, 143, 147, 150, 156, 160, 164, 168, 172, 176, 180, 183, 187, 191, 197, 201, 205, 209, 213, 217, 221, 225, 229, 233, 237, 241, 245, 249, 251, 254, 256 };

//	Returns width of char drawn
u32 gfx_drawchar(char which, int x, int y, u16 drawcolors)
{
	u32 offset = FONT_6pxOffsets[26 + 26 + 10 + 2];
	u32 offsetSize = FONT_6pxOffsets[26 + 26 + 10 + 1 + 2] - offset;
	
	if( which >= 'A' && which <= 'Z')
	{
		offset = FONT_6pxOffsets[which - 'A'];
		offsetSize = FONT_6pxOffsets[which - 'A' + 1] - offset;
	}
	else if( which >= 'a' && which <= 'z')
	{
		offset = FONT_6pxOffsets[which - 'a' + 26];
		offsetSize = FONT_6pxOffsets[which - 'a' + 26 + 1] - offset;
	}
	else if( which >= '0' && which <= '9')
	{
		offset = FONT_6pxOffsets[which - '0' + 26 + 26];
		offsetSize = FONT_6pxOffsets[which - '0' + 26 + 26 + 1] - offset;
	}
	else if( which == '.')
	{
		offset = FONT_6pxOffsets[26 + 26 + 10 + 0];
		offsetSize = FONT_6pxOffsets[26 + 26 + 10 + 0 + 1] - offset;
	}
	else if( which == ',')
	{
		offset = FONT_6pxOffsets[26 + 26 + 10 + 1];
		offsetSize = FONT_6pxOffsets[26 + 26 + 10 + 1 + 1] - offset;
	}
	else if( which == '!')
	{
		offset = FONT_6pxOffsets[26 + 26 + 10 + 2];
		offsetSize = FONT_6pxOffsets[26 + 26 + 10 + 1 + 2] - offset;
	}
	else if( which == ' ')
	{
		return 2;
	}
	else
	{
		trace("Unknown drawchar!");
		return 0;
	}
	
	//*DRAW_COLORS = 0x0021;
	*DRAW_COLORS = drawcolors;
	blitSub(FONT_6px, x, y, offsetSize, FONT_6pxHeight, offset, 0, FONT_6pxWidth, FONT_6pxFlags);
	return offsetSize;
}

void gfx_drawstr(const char* str, int x, int y, u16 drawcolors)
{
	while( *str != '\0')
	{
		x += gfx_drawchar(*str, x, y, drawcolors);
		str++;
	}
}

void gfx_drawval(u32 val, int x, int y, u16 drawcolors)
{
	char buffer[256];
	tostr(buffer, val);
	gfx_drawstr(buffer, x, y, drawcolors);
}

void gfx_setpixel(int x, int y, int paletteColor)
{
	if (x > SCREEN_SIZE || y > SCREEN_SIZE)
	{
		return;
	}

	//uint8_t& pixel = FRAMEBUFFER[y*40 + x / 4];

    // The byte index into the framebuffer that contains (x, y)
    int idx = (y*160 + x) >> 2;

    // Calculate the bits within the byte that corresponds to our position
    int shift = (x & 0b11) << 1;
    int mask = 0b11 << shift;

	int color = paletteColor;

    // Write to the framebuffer
    FRAMEBUFFER[idx] = (u8)((color << shift) | (FRAMEBUFFER[idx] & ~mask));
}