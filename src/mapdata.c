#include "mapdata.h"

#if 0
#define ___ (0x00)
#define GRS (0xfe)  //  Grass tl/br

#define WHT (0x00)  //  Colors
#define LGT (0x01)
#define DRK (0x02)
#define BLK (0x03)

#define BSH (0x55)  //  Bush
#define PTH (0x54)  //  Path
#define FLW (0x3a)  //  Flower Small

#define TR1 (0x04)  //  Tree
#define TR2 (0x05)
#define TR3 (0x06)
#define TR4 (0x07)
#define TR5 (0x14)
#define TR6 (0x15)
#define TR7 (0x16)
#define TR8 (0x17)

#define TT1 (0x04)
#define TT2 (0x05)

#define RF1 (0x66)  //  Roof left1
#define RF2 (0x67)  //  Roof top
#define RF3 (0x68)  //  Roof right
#define RF4 (0x76)  //  Roof bl
#define RF5 (0x77)  //  Roof bottom
#define RF6 (0x78)  //  Roof br

#define HL1 (0x69)  //  House left
#define HR1 (0x79)  //  House right

#define DR1 (0x0e)  //  House door1
#define DR2 (0x0f)  //  House door2
#define DR3 (0x1e)  //  House door3
#define DR4 (0x1f)  //  House door4

#define WN1 (0x0c)  //  House window1
#define WN2 (0x0d)  //  House window2
#define WN3 (0x1c)  //  House window3
#define WN4 (0x1d)  //  House window4

//#define TRS (0x10)  //  treasure chest
//#define CR1 (0x31)

struct Screen TestScreen = {
TR1,TR2,TR3,TR4,TR1,TR2,TR3,TR4,BSH,BSH,BSH,BSH,BSH,BSH,TR1,TR2,TR3,TR4,TR1,TR2,
TR5,TR6,TR7,TR8,TR5,TR6,TR7,TR8,BSH,BSH,BSH,BSH,BSH,BSH,TR5,TR6,TR7,TR8,TR5,TR6,
PTH,PTH,PTH,PTH,RF1,RF2,RF2,RF2,RF2,RF3,BSH,BSH,FLW,___,FLW,___,FLW,___,FLW,___,
PTH,PTH,PTH,PTH,HL1,LGT,LGT,LGT,LGT,HR1,BSH,BSH,___,FLW,___,FLW,___,FLW,___,FLW,
FLW,___,PTH,PTH,HL1,LGT,LGT,LGT,LGT,HR1,FLW,___,FLW,___,FLW,___,FLW,___,FLW,___,
___,FLW,PTH,PTH,RF4,RF5,RF5,RF5,RF5,RF6,___,FLW,___,FLW,___,FLW,___,FLW,___,FLW,
FLW,___,PTH,PTH,WN1,WN2,DR1,DR2,WN1,WN2,FLW,___,FLW,___,BSH,BSH,FLW,___,FLW,___,
___,FLW,PTH,PTH,WN3,WN4,DR3,DR4,WN3,WN4,___,FLW,___,FLW,BSH,BSH,___,FLW,___,FLW,
FLW,___,PTH,PTH,PTH,PTH,PTH,PTH,PTH,PTH,BSH,BSH,BSH,BSH,BSH,BSH,BSH,BSH,FLW,___,
___,FLW,PTH,PTH,PTH,PTH,PTH,PTH,PTH,PTH,BSH,BSH,BSH,BSH,BSH,BSH,BSH,BSH,___,FLW,
FLW,___,FLW,___,FLW,___,BSH,BSH,BSH,BSH,BSH,BSH,BSH,BSH,BSH,BSH,FLW,___,FLW,___,
___,FLW,___,FLW,___,FLW,BSH,BSH,BSH,BSH,BSH,BSH,BSH,BSH,BSH,BSH,___,FLW,___,FLW,
PTH,PTH,PTH,PTH,FLW,___,FLW,___,FLW,___,FLW,___,FLW,___,FLW,___,FLW,___,FLW,___,
PTH,PTH,PTH,PTH,___,FLW,___,FLW,___,FLW,___,FLW,___,FLW,___,FLW,___,FLW,___,FLW,
FLW,___,PTH,PTH,PTH,PTH,PTH,PTH,PTH,PTH,PTH,PTH,PTH,PTH,PTH,PTH,PTH,PTH,PTH,PTH,
___,FLW,PTH,PTH,PTH,PTH,PTH,PTH,PTH,PTH,PTH,PTH,PTH,PTH,PTH,PTH,PTH,PTH,PTH,PTH,
FLW,___,FLW,___,FLW,___,FLW,___,FLW,___,FLW,___,FLW,___,FLW,___,FLW,___,FLW,___,
___,FLW,___,FLW,___,FLW,___,FLW,___,FLW,___,FLW,___,FLW,___,FLW,___,FLW,___,FLW,
 };
#endif

struct ScreenMeta SCR_Empty = {
Gras,Gras,Gras,Gras,Bush,Path,Gras,Gras,Gras,Gras,
Path,Path,Gras,Gras,Gras,Path,Gras,Gras,Gras,Gras,
Gras,Path,Gras,Gras,Gras,Path,Path,Gras,Gras,Gras,
Gras,Path,Gras,Gras,Gras,Gras,Path,Bush,Gras,Gras,
Gras,Path,Path,Path,Path,Bush,Path,Bush,Bush,Gras,
Gras,Gras,Gras,Bush,Bush,Path,Path,Bush,Gras,Gras,
Path,Path,Gras,Gras,Gras,Path,Path,Gras,Gras,Gras,
Gras,Path,Path,Path,Path,Path,Path,Path,Path,Path,
Gras,Gras,Gras,Gras,Gras,Path,Gras,Gras,Gras,Gras,
};

struct ScreenMeta SCR_Empt2 = {
Gras,Gras,Gras,Gras,Bush,Path,Gras,Gras,Gras,Gras,
Path,Path,Gras,Gras,Gras,Path,Gras,Gras,Gras,Gras,
Gras,Path,Gras,Gras,Gras,Path,Path,Gras,Gras,Gras,
Gras,Path,Gras,Gras,Gras,Gras,Path,Bush,Gras,Gras,
Gras,Path,Path,Path,Path,Bush,Path,Bush,Bush,Gras,
Gras,Gras,Gras,Bush,Bush,Path,Path,Bush,Gras,Gras,
Path,Path,Gras,Gras,Gras,Path,Path,Gras,Gras,Gras,
Gras,Path,Path,Path,Path,Path,Path,Path,Path,Path,
Gras,Gras,Gras,Gras,Gras,Path,Gras,Gras,Gras,Gras,
};

struct ScreenMeta SCR_Empt3 = {
Gras,Gras,Gras,Gras,Bush,Path,Gras,Gras,Gras,Gras,
Path,Path,Gras,Gras,Gras,Path,Gras,Gras,Gras,Gras,
Gras,Path,Gras,Gras,Gras,Path,Path,Gras,Gras,Gras,
Gras,Path,Gras,Gras,Gras,Gras,Path,Bush,Gras,Gras,
Gras,Path,Path,Path,Path,Bush,Path,Bush,Bush,Gras,
Gras,Gras,Gras,Bush,Bush,Path,Path,Bush,Gras,Gras,
Path,Path,Gras,Gras,Gras,Path,Path,Gras,Gras,Gras,
Gras,Path,Path,Path,Path,Path,Path,Path,Path,Path,
Gras,Gras,Gras,Gras,Gras,Path,Gras,Gras,Gras,Gras,
};

struct ScreenMeta SCR_Empt4 = {
Gras,Gras,Gras,Gras,Bush,Path,Gras,Gras,Gras,Gras,
Path,Path,Gras,Gras,Gras,Path,Gras,Gras,Gras,Gras,
Gras,Path,Gras,Gras,Gras,Path,Path,Gras,Gras,Gras,
Gras,Path,Gras,Gras,Gras,Gras,Path,Bush,Gras,Gras,
Gras,Path,Path,Path,Path,Bush,Path,Bush,Bush,Gras,
Gras,Gras,Gras,Bush,Bush,Path,Path,Bush,Gras,Gras,
Path,Path,Gras,Gras,Gras,Path,Path,Gras,Gras,Gras,
Gras,Path,Path,Path,Path,Path,Path,Path,Path,Path,
Gras,Gras,Gras,Gras,Gras,Path,Gras,Gras,Gras,Gras,
};

struct ScreenMeta SCR_Empt5 = {
Gras,Gras,Gras,Gras,Bush,Path,Gras,Gras,Gras,Gras,
Path,Path,Gras,Gras,Gras,Path,Gras,Gras,Gras,Gras,
Gras,Path,Gras,Gras,Gras,Path,Path,Gras,Gras,Gras,
Gras,Path,Gras,Gras,Gras,Gras,Path,Bush,Gras,Gras,
Gras,Path,Path,Path,Path,Bush,Path,Bush,Bush,Gras,
Gras,Gras,Gras,Bush,Bush,Path,Path,Bush,Gras,Gras,
Path,Path,Gras,Gras,Gras,Path,Path,Gras,Gras,Gras,
Gras,Path,Path,Path,Path,Path,Path,Path,Path,Path,
Gras,Gras,Gras,Gras,Gras,Path,Gras,Gras,Gras,Gras,
};

struct ScreenMeta SCR_Empt6 = {
Gras,Gras,Gras,Gras,Bush,Path,Gras,Gras,Gras,Gras,
Path,Path,Gras,Gras,Gras,Path,Gras,Gras,Gras,Gras,
Gras,Path,Gras,Gras,Gras,Path,Path,Gras,Gras,Gras,
Gras,Path,Gras,Gras,Gras,Gras,Path,Bush,Gras,Gras,
Gras,Path,Path,Path,Path,Bush,Path,Bush,Bush,Gras,
Gras,Gras,Gras,Bush,Bush,Path,Path,Bush,Gras,Gras,
Path,Path,Gras,Gras,Gras,Path,Path,Gras,Gras,Gras,
Gras,Path,Path,Path,Path,Path,Path,Path,Path,Path,
Gras,Gras,Gras,Gras,Gras,Path,Gras,Gras,Gras,Gras,
};

struct ScreenMeta SCR_Empt7 = {
Gras,Gras,Gras,Gras,Bush,Path,Gras,Gras,Gras,Gras,
Path,Path,Gras,Gras,Gras,Path,Gras,Gras,Gras,Gras,
Gras,Path,Gras,Gras,Gras,Path,Path,Gras,Gras,Gras,
Gras,Path,Gras,Gras,Gras,Gras,Path,Bush,Gras,Gras,
Gras,Path,Path,Path,Path,Bush,Path,Bush,Bush,Gras,
Gras,Gras,Gras,Bush,Bush,Path,Path,Bush,Gras,Gras,
Path,Path,Gras,Gras,Gras,Path,Path,Gras,Gras,Gras,
Gras,Path,Path,Path,Path,Path,Path,Path,Path,Path,
Gras,Gras,Gras,Gras,Gras,Path,Gras,Gras,Gras,Gras,
};

struct ScreenMeta SCR_Empt8 = {
Gras,Gras,Gras,Gras,Bush,Path,Gras,Gras,Gras,Gras,
Path,Path,Gras,Gras,Gras,Path,Gras,Gras,Gras,Gras,
Gras,Path,Gras,Gras,Gras,Path,Path,Gras,Gras,Gras,
Gras,Path,Gras,Gras,Gras,Gras,Path,Bush,Gras,Gras,
Gras,Path,Path,Path,Path,Bush,Path,Bush,Bush,Gras,
Gras,Gras,Gras,Bush,Bush,Path,Path,Bush,Gras,Gras,
Path,Path,Gras,Gras,Gras,Path,Path,Gras,Gras,Gras,
Gras,Path,Path,Path,Path,Path,Path,Path,Path,Path,
Gras,Gras,Gras,Gras,Gras,Path,Gras,Gras,Gras,Gras,
};

struct ScreenMeta SCR_Empt9 = {
Gras,Gras,Gras,Gras,Bush,Path,Gras,Gras,Gras,Gras,
Path,Path,Gras,Gras,Gras,Path,Gras,Gras,Gras,Gras,
Gras,Path,Gras,Gras,Gras,Path,Path,Gras,Gras,Gras,
Gras,Path,Gras,Gras,Gras,Gras,Path,Bush,Gras,Gras,
Gras,Path,Path,Path,Path,Bush,Path,Bush,Bush,Gras,
Gras,Gras,Gras,Bush,Bush,Path,Path,Bush,Gras,Gras,
Path,Path,Gras,Gras,Gras,Path,Path,Gras,Gras,Gras,
Gras,Path,Path,Path,Path,Path,Path,Path,Path,Path,
Gras,Gras,Gras,Gras,Gras,Path,Gras,Gras,Gras,Gras,
};

struct ScreenMeta SCR_EmptA = {
Gras,Gras,Gras,Gras,Bush,Path,Gras,Gras,Gras,Gras,
Path,Path,Gras,Gras,Gras,Path,Gras,Gras,Gras,Gras,
Gras,Path,Gras,Gras,Gras,Path,Path,Gras,Gras,Gras,
Gras,Path,Gras,Gras,Gras,Gras,Path,Bush,Gras,Gras,
Gras,Path,Path,Path,Path,Bush,Path,Bush,Bush,Gras,
Gras,Gras,Gras,Bush,Bush,Path,Path,Bush,Gras,Gras,
Path,Path,Gras,Gras,Gras,Path,Path,Gras,Gras,Gras,
Gras,Path,Path,Path,Path,Path,Path,Path,Path,Path,
Gras,Gras,Gras,Gras,Gras,Path,Gras,Gras,Gras,Gras,
};

struct ScreenMeta SCR_EmptB = {
Gras,Gras,Gras,Gras,Bush,Path,Gras,Gras,Gras,Gras,
Path,Path,Gras,Gras,Gras,Path,Gras,Gras,Gras,Gras,
Gras,Path,Gras,Gras,Gras,Path,Path,Gras,Gras,Gras,
Gras,Path,Gras,Gras,Gras,Gras,Path,Bush,Gras,Gras,
Gras,Path,Path,Path,Path,Bush,Path,Bush,Bush,Gras,
Gras,Gras,Gras,Bush,Bush,Path,Path,Bush,Gras,Gras,
Path,Path,Gras,Gras,Gras,Path,Path,Gras,Gras,Gras,
Gras,Path,Path,Path,Path,Path,Path,Path,Path,Path,
Gras,Gras,Gras,Gras,Gras,Path,Gras,Gras,Gras,Gras,
};

struct ScreenMeta SCR_EmptC = {
Gras,Gras,Gras,Gras,Bush,Path,Gras,Gras,Gras,Gras,
Path,Path,Gras,Gras,Gras,Path,Gras,Gras,Gras,Gras,
Gras,Path,Gras,Gras,Gras,Path,Path,Gras,Gras,Gras,
Gras,Path,Gras,Gras,Gras,Gras,Path,Bush,Gras,Gras,
Gras,Path,Path,Path,Path,Bush,Path,Bush,Bush,Gras,
Gras,Gras,Gras,Bush,Bush,Path,Path,Bush,Gras,Gras,
Path,Path,Gras,Gras,Gras,Path,Path,Gras,Gras,Gras,
Gras,Path,Path,Path,Path,Path,Path,Path,Path,Path,
Gras,Gras,Gras,Gras,Gras,Path,Gras,Gras,Gras,Gras,
};

struct ScreenMeta SCR_EmptD = {
Gras,Gras,Gras,Gras,Bush,Path,Gras,Gras,Gras,Gras,
Path,Path,Gras,Gras,Gras,Path,Gras,Gras,Gras,Gras,
Gras,Path,Gras,Gras,Gras,Path,Path,Gras,Gras,Gras,
Gras,Path,Gras,Gras,Gras,Gras,Path,Bush,Gras,Gras,
Gras,Path,Path,Path,Path,Bush,Path,Bush,Bush,Gras,
Gras,Gras,Gras,Bush,Bush,Path,Path,Bush,Gras,Gras,
Path,Path,Gras,Gras,Gras,Path,Path,Gras,Gras,Gras,
Gras,Path,Path,Path,Path,Path,Path,Path,Path,Path,
Gras,Gras,Gras,Gras,Gras,Path,Gras,Gras,Gras,Gras,
};

struct ScreenMeta SCR_EmptE = {
Gras,Gras,Gras,Gras,Bush,Path,Gras,Gras,Gras,Gras,
Path,Path,Gras,Gras,Gras,Path,Gras,Gras,Gras,Gras,
Gras,Path,Gras,Gras,Gras,Path,Path,Gras,Gras,Gras,
Gras,Path,Gras,Gras,Gras,Gras,Path,Bush,Gras,Gras,
Gras,Path,Path,Path,Path,Bush,Path,Bush,Bush,Gras,
Gras,Gras,Gras,Bush,Bush,Path,Path,Bush,Gras,Gras,
Path,Path,Gras,Gras,Gras,Path,Path,Gras,Gras,Gras,
Gras,Path,Path,Path,Path,Path,Path,Path,Path,Path,
Gras,Gras,Gras,Gras,Gras,Path,Gras,Gras,Gras,Gras,
};

struct ScreenMeta SCR_House = {
Tre3,Tre4,Tre3,Tre4,Bush,Bush,Bush,Tre3,Tre4,Tre3,
Path,Path,RfTL,RfTC,RfTR,Bush,Gras,Gras,Gras,Gras,
Gras,Path,RfBL,RfBC,RfBR,Kenl,Gra2,IWal,Gras,Gras,
Gras,Path,HsWn,HsDr,HsWn,HsDr,Fenc,Bush,Gras,Gras,
Gras,Path,Path,Path,Path,Bush,Bush,Bush,Bush,Gras,
Gras,Gras,Gra2,Bush,Bush,Bush,Bush,Bush,Gras,Gras,
Path,Path,Gras,Gras,Gras,Gras,Gras,Gras,Gra2,Gras,
Gras,Path,Path,Path,Path,Path,Path,Path,Path,Path,
Gras,Gras,Gras,Gras,Gras,Gras,Gras,Gras,Gras,Gras,
};

struct ScreenMeta SCR_Start = {
Tre3,Tre4,Tre3,Tre4,Tre3,Tre4,Tre3,Tre4,Tre3,Tre4,
Gras,Gras,Gras,Gras,Gras,Gras,Gras,Gras,Gras,Gras,
Gras,Gras,Gras,Gras,Gras,Gras,Gras,Gras,Gras,Gras,
Gras,Gras,Gras,Gras,Gras,Gras,Gras,Bush,Gras,Gras,
Gras,Path,Path,Path,Path,Path,Bush,Bush,Bush,Gras,
Gras,Path,Gras,Path,Path,Path,Bush,Bush,Gras,Gras,
Gras,Path,Gras,Gras,Gras,Gras,Gras,Gras,Gras,Gras,
Gras,Gras,Gras,Gras,Gras,Gras,Gras,Gras,Gras,Gras,
Gras,Path,Path,Path,Path,Path,Path,Path,Path,Path,
};

struct WorldMap MainWorldMap = {
    &SCR_Empty,&SCR_Empt2,&SCR_Empt3,&SCR_Empt4,
    &SCR_Empt5,&SCR_Empt6,&SCR_Empt7,&SCR_Empt8,
    &SCR_Empt9,&SCR_Start,&SCR_House,&SCR_EmptA,
    &SCR_EmptB,&SCR_EmptC,&SCR_EmptD,&SCR_EmptE };


//  Return flags
uint32_t get_meta_tile_info(MetaTile metaTile, uint8_t* TL, uint8_t* TR, uint8_t* BL, uint8_t* BR)
{
    switch(metaTile)
    {  
        case Empt:
        case IWal:
        *TL = 0x00;
        *TR = 0x00;
        *BL = 0x00;
        *BR = 0x00;
        return 0;

        case Gras:
        *TL = 0x3a;
        *TR = 0x00;
        *BL = 0x00;
        *BR = 0x3a;
        return 0;

        case Gra2:
        *TL = 0x00;
        *TR = 0x3a;
        *BL = 0x3a;
        *BR = 0x00;
        return 0;
        
        case Bush:
        *TL = *TR = *BL = *BR = 0x55;
        return 0;

        case Path:
        *TL = *TR = *BL = *BR = 0x54;
        return 0;

        case HsWn:
        *TL = 0x0c;
        *TR = 0x0d;
        *BL = 0x1c;
        *BR = 0x1d;
        return 0;

        case HsDr:
        *TL = 0x0e;
        *TR = 0x0f;
        *BL = 0x1e;
        *BR = 0x1f;
        return 0;

        case RfTL:
        *TL = 0x66;
        *TR = 0x67;
        *BL = 0x69;
        *BR = 0x01;
        return 0;

        case RfTC:
        *TL = 0x67;
        *TR = 0x67;
        *BL = 0x01;
        *BR = 0x01;
        return 0;

        case RfTR:
        *TL = 0x67;
        *TR = 0x68;
        *BL = 0x01;
        *BR = 0x79;
        return 0;

        case RfBL:
        *TL = 0x69;
        *TR = 0x01;
        *BL = 0x76;
        *BR = 0x77;
        return 0;

        case RfBC:
        *TL = 0x01;
        *TR = 0x01;
        *BL = 0x77;
        *BR = 0x77;
        return 0;

        case RfBR:
        *TL = 0x01;
        *TR = 0x79;
        *BL = 0x77;
        *BR = 0x78;
        return 0;


        case Tre3:
        *TL = 0x04;
        *TR = 0x05;
        *BL = 0x14;
        *BR = 0x15;
        return 0;

        case Tre4:
        *TL = 0x06;
        *TR = 0x07;
        *BL = 0x16;
        *BR = 0x17;
        return 0;

        case Kenl:
        *TL = 0x3e;
        *TR = 0x3e;
        *BL = 0x3f;
        *BR = 0x3f;
        return 0;

        case Fenc:
        *TL = 0x6c;
        *TR = 0x6c;
        *BL = 0x7c;
        *BR = 0x7c;
        return 0;

        default:
        *TL = 0x00;
        *TR = 0x01;
        *BL = 0x02;
        *BR = 0x03;
        return 0;
    }
}

bool can_move_onto_tile(MetaTile metaTile)
{
    switch(metaTile)
    {
        case Empt:
        case Gras:
        case Gra2:
        case Bush:
        case Path:
        case HsDr:
        return true;

        default:
        return false;
    }
}

struct ScreenMeta* get_screen(uint8_t x, uint8_t y)
{
    return MainWorldMap.World[x+y*WORLD_MAX_X];
}