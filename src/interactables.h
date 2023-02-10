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