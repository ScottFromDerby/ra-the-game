#include "wasm4.h"
#include "interactables.h"
#include "main.h"
#include "dialog.h"

struct Interactable g_Interactables[NUM_INTERACTABLES];

struct Interactable* g_currentInteractable = 0;

void clear_interactables()
{
    for( int i = 0 ; i < NUM_INTERACTABLES; ++i)
    {
        g_Interactables->type = IT_None;
        g_Interactables->interactableFlags = 0;
    }
}

void add_interactable(enum InteractableType type, u8 xPos, u8 yPos, u8 interactableFlags)
{
    for (int i = 0; i < NUM_INTERACTABLES; ++i)
    {
        if (g_Interactables[i].type == IT_None)
        {
            g_Interactables->type = type;
            g_Interactables->xPos = xPos;
            g_Interactables->yPos = yPos;
            g_Interactables->interactableFlags = interactableFlags;
            return;
        }
    }

    trace("Can't add interactable?!");
}

void tick_interactable(struct Interactable* pInteractable)
{
    pInteractable->ticks++;
    switch( pInteractable->type )
    {
        case IT_None:
        break;
        case IT_StartTestNPC:
            if( pInteractable->ticks == 30)
            {
                pInteractable->ticks = 0;
                pInteractable->gfxPhase = (pInteractable->gfxPhase + 1) % 2;
            }
        break;
        case IT_AnotherNPC:
            if( pInteractable->ticks == 30)
            {
                pInteractable->ticks = 0;
                pInteractable->gfxPhase = (pInteractable->gfxPhase + 1) % 2;
            }
        break;
    }
}

void tick_interactables()
{
    for (int i = 0; i < NUM_INTERACTABLES; ++i)
    {
        if (g_Interactables[i].type != IT_None)
        {
            tick_interactable(&g_Interactables[i]);
        }
    }
}

void on_interact(struct Interactable* pInteractedWith)
{
    switch( pInteractedWith->type )
    {
        case IT_StartTestNPC:
            g_currentInteractable = pInteractedWith;
            if( g_currentInteractable->interactPhase == 0)
            {
                show_dialog("I'm the first NPC", "I give basic information", "Would you like a multi...");
                g_currentInteractable->interactPhase = 1;
            }
            else if( g_currentInteractable->interactPhase == 1)
            {
                show_dialog("dialog prompt? Well there you", "go you got one! Now scram", "get outta here!");
                g_currentInteractable->interactPhase = 2;
            }
            else if( g_currentInteractable->interactPhase == 2 )
            {
                close_dialog();
                g_currentInteractable->interactPhase = 0;
                g_currentInteractable = 0;
            }
        break;

        case IT_AnotherNPC:
            g_currentInteractable = pInteractedWith;
            if( g_currentInteractable->interactPhase == 0)
            {
                show_dialog("I'm the guy to hand out", "shields, but I ran out. I wonder", "if you could go get one?");
                g_currentInteractable->interactPhase = 1;
            }
            else if( g_currentInteractable->interactPhase == 1)
            {
                show_dialog("There aren't any yes or", "no prompts yet.", "");
                g_currentInteractable->interactPhase = 2;
            }
            else if( g_currentInteractable->interactPhase == 2)
            {
                show_dialog("Sorry.", "", "");
                g_currentInteractable->interactPhase = 3;
            }
            else if( g_currentInteractable->interactPhase == 3 )
            {
                close_dialog();
                g_currentInteractable->interactPhase = 0;
                g_currentInteractable = 0;
            }
        break;
        case IT_None:
        break;
    }
}

void on_dialog_confirm()
{
    if (g_currentInteractable != 0)
    {
        on_interact(g_currentInteractable);
    }
}