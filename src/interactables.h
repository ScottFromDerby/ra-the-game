#pragma once

#include "wasm4.h"

enum
{
    NUM_INTERACTABLES = 4,
};

enum InteractableType
{
    IT_None,
    IT_StartTestNPC,
    IT_AnotherNPC,
    IT_MusicBox,
    IT_RA_NPC01,
    IT_RA_NPC02,
    IT_RA_NPC03,
    IT_RA_NPC04,
};

enum    //  Bitwise
{
    INTERACTABLE_ACTIVE = (1<<0),
    INTERACTABLE_BLOCK_PLAYER = (1<<1),
};

struct Interactable
{
    enum InteractableType type;
    u8 xPos;
    u8 yPos;
    u8 ticks;
    u8 gfxPhase;
    u8 interactPhase;
    u8 interactableFlags;
};

extern struct Interactable g_Interactables[NUM_INTERACTABLES];

extern struct Interactable* g_currentInteractable;

void clear_interactables();

void add_interactable(enum InteractableType type, u8 xPos, u8 yPos, u8 interactableFlags);

void tick_interactables();

void on_interact(struct Interactable* pInteractedWith);

void on_dialog_confirm();