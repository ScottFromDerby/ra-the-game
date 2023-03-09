#pragma once

#include "wasm4.h"

enum
{
    MAX_NUM_ENEMIES = 4,
};

enum EnemyType
{
    ET_None,
    ET_Octorok,
    ET_OctorokBullet,
    //IT_None,
    //IT_StartTestNPC,
    //IT_AnotherNPC,
    //IT_MusicBox,
    //IT_RA_NPC01,
    //IT_RA_NPC02,
    //IT_RA_NPC03,
    //IT_RA_NPC04,
};

//enum    //  Bitwise
//{
    //INTERACTABLE_ACTIVE = (1<<0),
    //INTERACTABLE_BLOCK_PLAYER = (1<<1),
//};

enum Octorok_Logic
{
    OL_Wandering,
    OL_Wait,
    OL_Fire,
};

struct Enemy
{
    enum EnemyType type;
    u8 xPos;
    u8 yPos;
    u8 ticks;
    int ticksToNextPhase;
    u8 gfxPhase;
    u8 logicPhase;
    u8 health;
    int flags;
};

extern struct Enemy g_Enemies[MAX_NUM_ENEMIES];

void clear_enemies();

void add_enemy(enum EnemyType type, u8 xPos, u8 yPos);

void tick_enemies();

void draw_enemies();