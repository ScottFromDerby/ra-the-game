#include "player.h"
#include "collectable.h"
#include "main.h"
#include "mapdata.h"
#include "rendering.h"
#include "gfx_weapon.h"
#include "gfx_player.h"
#include "tools.h"
#include "vfx.h"

enum SwordSwingState g_swordSwingState = Swing_Off;
u8 g_swordSwingTicks = 0;

int g_playerNumHalfHearts = 12;
int g_playerMaxNumHalfHearts = 24;
int g_playerNumCoins = 69;

void start_swing_sword()
{
    g_swordSwingState = Swing_Side;
    g_swordSwingTicks = 0;
}

void draw_player_sprite()
{
    u32 spriteSheetOffsetX = 0;
    u32 spriteSheetOffsetY = 0;
    u32 spriteSheetRenderFlags = 0;
    switch (g_currentFacing)
    {
    case Up:
        spriteSheetOffsetX = TILESIZE;
        spriteSheetOffsetY = TILESIZE;
        spriteSheetRenderFlags = (((g_upHeldFrames + 6) % 14) > 7) ? BLIT_FLIP_X : 0;
        break;
    case Down:
        spriteSheetOffsetX = 0;
        spriteSheetOffsetY = TILESIZE;
        spriteSheetRenderFlags = (((g_downHeldFrames + 6) % 14) > 7) ? BLIT_FLIP_X : 0;
        break;
    case Right:
        spriteSheetOffsetX = (((g_rightHeldFrames + 6) % 14) > 7) ? 48 : 32;
        spriteSheetOffsetY = TILESIZE;
        spriteSheetRenderFlags = BLIT_FLIP_X;
        break;
    case Left:
        spriteSheetOffsetX = (((g_leftHeldFrames + 6) % 14) > 7) ? 48 : 32;
        spriteSheetOffsetY = TILESIZE;
        spriteSheetRenderFlags = 0;
        break;
    default:
        break;
    }

    int playerExtraOffsetX = 0;
    int playerExtraOffsetY = 0;
    if (g_transitionFramesLeft > 0)
    {
        if (g_transitionDirection == Left)
        {
            playerExtraOffsetX = -g_transitionFramesLeft;
        }
        else if (g_transitionDirection == Right)
        {
            playerExtraOffsetX = g_transitionFramesLeft;
        }

        if (g_transitionDirection == Up)
        {
            playerExtraOffsetY = -g_transitionFramesLeft;
        }
        else if (g_transitionDirection == Down)
        {
            playerExtraOffsetY = g_transitionFramesLeft;
        }
    }

    u16 NORMAL_PLY_SPRITE = 0x0421;
    u16 INVERTED_PLY_SPRITE = 0x0234;
    if (g_damageFramesLeft > 0)
    {   
        *DRAW_COLORS = (g_damageFramesLeft % 8 > 4 ) ? NORMAL_PLY_SPRITE : INVERTED_PLY_SPRITE;
    }
    else
    {
        *DRAW_COLORS = NORMAL_PLY_SPRITE;
    }
    

    if (g_swordSwingState == Swing_Off)
    {
        //  Regular
        blitSub(SPRITE_Player, g_playerX - HALFTILE + playerExtraOffsetX, g_playerY - HALFTILE + playerExtraOffsetY, TILESIZE, TILESIZE, spriteSheetOffsetX, spriteSheetOffsetY, SPRITE_PlayerWidth, SPRITE_PlayerFlags | spriteSheetRenderFlags);
    }
    else if (g_swordSwingState == Swing_Side)
    {
        blitSub(SPRITE_Player, g_playerX - HALFTILE + playerExtraOffsetX, g_playerY - HALFTILE + playerExtraOffsetY, TILESIZE, TILESIZE, spriteSheetOffsetX, spriteSheetOffsetY, SPRITE_PlayerWidth, SPRITE_PlayerFlags | spriteSheetRenderFlags);
    }
    else if (g_swordSwingState == Swing_Diagonal)
    {
        blitSub(SPRITE_Player, g_playerX - HALFTILE + playerExtraOffsetX, g_playerY - HALFTILE + playerExtraOffsetY, TILESIZE, TILESIZE, spriteSheetOffsetX, spriteSheetOffsetY, SPRITE_PlayerWidth, SPRITE_PlayerFlags | spriteSheetRenderFlags);
    }
    else if (g_swordSwingState == Swing_Forwards)
    {
        *DRAW_COLORS = 0x0421;

        // tracef("Swingforwards plysprite %u", g_currentFacing);

        u32 tileWantedX = TILESIZE * 2;
        u32 tileWantedY = TILESIZE * 3;

        if (g_currentFacing == Left)
        {
            spriteSheetRenderFlags = 0;
            tileWantedX = TILESIZE * 2;
            tileWantedY = TILESIZE * 3;
        }
        else if (g_currentFacing == Right)
        {
            spriteSheetRenderFlags = BLIT_FLIP_X;
            tileWantedX = TILESIZE * 2;
            tileWantedY = TILESIZE * 3;
        }
        else if (g_currentFacing == Up)
        {
            spriteSheetRenderFlags = 0;
            tileWantedX = TILESIZE * 1;
            tileWantedY = TILESIZE * 3;
            playerExtraOffsetY = -2;
        }
        else if (g_currentFacing == Down)
        {
            spriteSheetRenderFlags = 0;
            tileWantedX = TILESIZE * 0;
            tileWantedY = TILESIZE * 3;
            playerExtraOffsetY = 2;
        }

        blitSub(SPRITE_Player, g_playerX - HALFTILE + playerExtraOffsetX, g_playerY - HALFTILE + playerExtraOffsetY, TILESIZE, TILESIZE, tileWantedX, tileWantedY, SPRITE_PlayerWidth, SPRITE_PlayerFlags | spriteSheetRenderFlags);
    }
}

void draw_weapon()
{
    //g_playerX = 90;
    //g_playerY = 90;

    //trace("draw_weapon");
    switch (g_currentFacing)
    {
        case Down:
        switch (g_swordSwingState)
        {
            case Swing_Side:
                *DRAW_COLORS = 0x0421;
                trace("downswing side");
                blitSub(SPRITE_Weapon, g_playerX-16, g_playerY, HALFTILE, HALFTILE, HALFTILE * 4, HALFTILE * 1, SPRITE_WeaponWidth, SPRITE_WeaponFlags);
                blitSub(SPRITE_Weapon, g_playerX-24, g_playerY, HALFTILE, HALFTILE, HALFTILE * 3, HALFTILE * 1, SPRITE_WeaponWidth, SPRITE_WeaponFlags);
            break;
            case Swing_Diagonal:
                *DRAW_COLORS = 0x0421;
                trace("downswing diagonal");
                blitSub(SPRITE_Weapon, g_playerX-21, g_playerY+6, TILESIZE, TILESIZE, HALFTILE * 5, HALFTILE * 0, SPRITE_WeaponWidth, SPRITE_WeaponFlags | BLIT_ROTATE);
            break;
            case Swing_Forwards:
                *DRAW_COLORS = 0x0421;
                trace("downswing forwards");
                blitSub(SPRITE_Weapon, g_playerX, g_playerY+10, HALFTILE, HALFTILE, HALFTILE * 2, HALFTILE * 0, SPRITE_WeaponWidth, SPRITE_WeaponFlags);
                blitSub(SPRITE_Weapon, g_playerX, g_playerY+18, HALFTILE, HALFTILE, HALFTILE * 2, HALFTILE * 1, SPRITE_WeaponWidth, SPRITE_WeaponFlags);
            break;

            case Swing_Off:
            default:
            break;
        }
        break;
        case Left:
        
        switch (g_swordSwingState)
        {
            case Swing_Side:
                *DRAW_COLORS = 0x0421;
                trace("leftswing side");
                blitSub(SPRITE_Weapon, g_playerX-8, g_playerY-16, HALFTILE, HALFTILE, HALFTILE * 2, HALFTILE * 0, SPRITE_WeaponWidth, SPRITE_WeaponFlags | BLIT_FLIP_Y);
                blitSub(SPRITE_Weapon, g_playerX-8, g_playerY-24, HALFTILE, HALFTILE, HALFTILE * 2, HALFTILE * 1, SPRITE_WeaponWidth, SPRITE_WeaponFlags | BLIT_FLIP_Y);
            break;
            case Swing_Diagonal:
                *DRAW_COLORS = 0x0421;
                trace("leftswing diagonal");
                blitSub(SPRITE_Weapon, g_playerX-20, g_playerY-21, TILESIZE, TILESIZE, HALFTILE * 5, HALFTILE * 0, SPRITE_WeaponWidth, SPRITE_WeaponFlags);
            break;
            case Swing_Forwards:
                *DRAW_COLORS = 0x0421;
                trace("leftswing forwards");
                blitSub(SPRITE_Weapon, g_playerX-16, g_playerY, HALFTILE, HALFTILE, HALFTILE * 4, HALFTILE * 1, SPRITE_WeaponWidth, SPRITE_WeaponFlags);
                blitSub(SPRITE_Weapon, g_playerX-24, g_playerY, HALFTILE, HALFTILE, HALFTILE * 3, HALFTILE * 1, SPRITE_WeaponWidth, SPRITE_WeaponFlags);
            break;

            case Swing_Off:
            default:
            break;
        }
        break;
        case Right:
        
        switch (g_swordSwingState)
        {
            case Swing_Side:
                *DRAW_COLORS = 0x0421;
                trace("rightswing side");
                blitSub(SPRITE_Weapon, g_playerX, g_playerY-16, HALFTILE, HALFTILE, HALFTILE * 2, HALFTILE * 0, SPRITE_WeaponWidth, SPRITE_WeaponFlags | BLIT_FLIP_Y);
                blitSub(SPRITE_Weapon, g_playerX, g_playerY-24, HALFTILE, HALFTILE, HALFTILE * 2, HALFTILE * 1, SPRITE_WeaponWidth, SPRITE_WeaponFlags | BLIT_FLIP_Y);
            break;
            case Swing_Diagonal:
                *DRAW_COLORS = 0x0421;
                trace("rightswing diagonal");
                blitSub(SPRITE_Weapon, g_playerX+5, g_playerY-21, TILESIZE, TILESIZE, HALFTILE * 5, HALFTILE * 0, SPRITE_WeaponWidth, SPRITE_WeaponFlags | BLIT_FLIP_X);
            break;
            case Swing_Forwards:
                *DRAW_COLORS = 0x0421;
                trace("rightswing forwards");
                blitSub(SPRITE_Weapon, g_playerX+8, g_playerY, HALFTILE, HALFTILE, HALFTILE * 4, HALFTILE * 1, SPRITE_WeaponWidth, SPRITE_WeaponFlags | BLIT_FLIP_X);
                blitSub(SPRITE_Weapon, g_playerX+16, g_playerY, HALFTILE, HALFTILE, HALFTILE * 3, HALFTILE * 1, SPRITE_WeaponWidth, SPRITE_WeaponFlags | BLIT_FLIP_X);
            break;

            case Swing_Off:
            default:
            break;
        }
        break;
        case Up:
        switch (g_swordSwingState)
        {
            case Swing_Side:
                *DRAW_COLORS = 0x0421;
                trace("upswing side");
                blitSub(SPRITE_Weapon, g_playerX+7, g_playerY- 8, HALFTILE, HALFTILE, HALFTILE * 4, HALFTILE * 1, SPRITE_WeaponWidth, SPRITE_WeaponFlags | BLIT_FLIP_X);
                blitSub(SPRITE_Weapon, g_playerX+15, g_playerY - 8, HALFTILE, HALFTILE, HALFTILE * 3, HALFTILE * 1, SPRITE_WeaponWidth, SPRITE_WeaponFlags | BLIT_FLIP_X);
            break;
            case Swing_Diagonal:
                *DRAW_COLORS = 0x0421;
                trace("upswing diagonal");
                blitSub(SPRITE_Weapon, g_playerX+5, g_playerY-22, TILESIZE, TILESIZE, HALFTILE * 5, HALFTILE * 0, SPRITE_WeaponWidth, SPRITE_WeaponFlags | BLIT_FLIP_X);
            break;
            case Swing_Forwards:
                *DRAW_COLORS = 0x0421;
                trace("upswing forwards");
                blitSub(SPRITE_Weapon, g_playerX-8, g_playerY-18, HALFTILE, HALFTILE, HALFTILE * 2, HALFTILE * 0, SPRITE_WeaponWidth, SPRITE_WeaponFlags | BLIT_FLIP_Y);
                blitSub(SPRITE_Weapon, g_playerX-8, g_playerY-26, HALFTILE, HALFTILE, HALFTILE * 2, HALFTILE * 1, SPRITE_WeaponWidth, SPRITE_WeaponFlags | BLIT_FLIP_Y);
            break;

            case Swing_Off:
            default:
            break;
        }
        break;

        default:
        break;
    }

}

void tick_weapon()
{
    switch(g_swordSwingState)
    {
        case Swing_Side:
        g_swordSwingTicks++;
        if( g_swordSwingTicks == 3)
        {
            g_swordSwingTicks = 0;
            g_swordSwingState = Swing_Diagonal;
        }
        break;

        case Swing_Diagonal:
        g_swordSwingTicks++;
        if( g_swordSwingTicks == 3)
        {
            g_swordSwingTicks = 0;
            g_swordSwingState = Swing_Forwards;
        }
        break;

        case Swing_Forwards:
        g_swordSwingTicks++;
        if( g_swordSwingTicks == 8)
        {
            g_swordSwingTicks = 0;
            g_swordSwingState = Swing_Off;
        }
        break;

        default:
        break;
    }

    //  Attempt cut grass
    if (g_swordSwingState == Swing_Forwards)
    {
        //  Check grass under middle of sword
        u8 tileX;
        u8 tileY;
        get_tile_infront_of_player(&tileX, &tileY);

        MetaTile tile = get_meta_tile(tileX, tileY);
        if (tile == TGrs)
        {
            for( int i = 0; i < 4; ++i )
            {
                //  Add vfx
                int startX;
                int startY;
                get_tile_centerpoint(tileX, tileY, &startX, &startY);
                startX += rand_range( -5, 5 );
                startY += rand_range( -5, 5 );
                int velX = (rand() % 2 == 0) ? rand_range( -4, -1 ) : rand_range( 1, 4 );
                int velY = (rand() % 2 == 0) ? rand_range( -4, -1 ) : rand_range( 1, 4 );
                add_vfx(VFX_LeafFoliage, startX, startY, velX, velY, 26, 0);
            }

            //  Maybe popup collectable
            if( rand() % 8 == 0 )
            {
                int centerX;
                int centerY;
                get_tile_centerpoint(tileX, tileY, &centerX, &centerY);
                add_collectable(COLL_Heart, centerX, centerY, 600);
            }
            else if( rand() % 8 == 0 )
            {
                int centerX;
                int centerY;
                get_tile_centerpoint(tileX, tileY, &centerX, &centerY);
                add_collectable(COLL_Coin, centerX, centerY, 600);
            }

            //  Set to grass
            g_currentScreen.screen_metatiles[tileX + tileY * NUM_TILES_WIDTH] = Gras;
        }
    }
}