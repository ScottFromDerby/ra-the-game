#include "wasm4.h"
#include "interactables.h"
#include "main.h"
#include "progress.h"
#include "dialog.h"

struct Interactable g_Interactables[NUM_INTERACTABLES];

struct Interactable* g_currentInteractable = 0;

void clear_interactables()
{
    for( int i = 0 ; i < NUM_INTERACTABLES; ++i)
    {
        g_Interactables[i].type = IT_None;
        g_Interactables[i].interactableFlags = 0;
    }
}

void add_interactable(enum InteractableType type, u8 xPos, u8 yPos, u8 interactableFlags)
{
    tracef("add_interactable: %d %d %d %d", type, xPos, yPos, interactableFlags);
    for (int i = 0; i < NUM_INTERACTABLES; ++i)
    {
        if (g_Interactables[i].type == IT_None)
        {
            g_Interactables[i].type = type;
            g_Interactables[i].xPos = xPos;
            g_Interactables[i].yPos = yPos;
            g_Interactables[i].interactableFlags = interactableFlags;
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
        case IT_RA_NPC01:
        case IT_RA_NPC02:
        case IT_RA_NPC03:
        case IT_RA_NPC04:
            if( pInteractable->ticks == 30)
            {
                pInteractable->ticks = 0;
                pInteractable->gfxPhase = (pInteractable->gfxPhase + 1) % 2;
            }
        break;
        case IT_MusicBox:
            if( g_Progress.musicBoxState == 1 && pInteractable->ticks == 30)
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

void do_start_test_npc()
{
    if( g_Progress.musicBoxState == 1)
    {
        toggle_dialog("Yes! Love this song! It reminds", "me of this kid I once knew.", "Looks a lot like you actually...");
    }
    else
    {
        if (g_currentInteractable->interactPhase == 0)
        {
            show_dialog("Hey, I recognise you! Aren't you the", "one that we found on the beach?", "It's pretty quiet around here.");
            g_currentInteractable->interactPhase = 1;
        }
        else if (g_currentInteractable->interactPhase == 1)
        {
            show_dialog("Do you like music? Try poking", "my spiky record player.", "");
            g_currentInteractable->interactPhase = 2;
        }
        else if (g_currentInteractable->interactPhase == 2)
        {
            close_dialog();
            g_currentInteractable->interactPhase = 3;
            g_currentInteractable = 0;
        }
        else if(g_currentInteractable->interactPhase == 3)
        {
            show_dialog("Can you talk to that spiky thing", "please? I think it will help.", "");
            g_currentInteractable->interactPhase = 4;
        }
        else if(g_currentInteractable->interactPhase == 4)
        {
            close_dialog();
            g_currentInteractable->interactPhase = 3;
            g_currentInteractable = 0;
        }
    }
}

void on_interact(struct Interactable* pInteractedWith)
{
    g_currentInteractable = pInteractedWith;
    if (g_currentInteractable == 0)
    {
        return;
    }
    
    switch (pInteractedWith->type)
    {
    case IT_StartTestNPC:
        do_start_test_npc();
        break;

    case IT_AnotherNPC:
        if (g_currentInteractable->interactPhase == 0)
        {
            show_dialog("I'm the guy to hand out", "shields, but I ran out. I wonder", "if you could go get one?");
            g_currentInteractable->interactPhase = 1;
        }
        else if (g_currentInteractable->interactPhase == 1)
        {
            show_dialog("There aren't any yes or", "no prompts yet.", "Sorry.");
            g_currentInteractable->interactPhase = 2;
        }
        else if (g_currentInteractable->interactPhase == 2)
        {
            show_dialog("Maybe you could help?", "Come to the RetroAchievements", "Discord and come help add them!");
            g_currentInteractable->interactPhase = 3;
        }
        else if (g_currentInteractable->interactPhase == 3)
        {
            close_dialog();
            g_currentInteractable->interactPhase = 0;
            g_currentInteractable = 0;
        }
        break;    
    case IT_MusicBox:
        trace("Music box interaction");
        if (g_bShowingDialogBG)
        {
            close_dialog();
        }
        else
        {
            if (g_Progress.musicBoxState == 0)
            {
                show_dialog("You switched it on.", "", "");
                g_Progress.musicBoxState = 1;
            }
            else
            {
                show_dialog("You switched it off.", "", "");
                g_Progress.musicBoxState = 0;
            }
        }
        break;
    case IT_RA_NPC01:
    case IT_RA_NPC02:
    case IT_RA_NPC03:
    case IT_RA_NPC04:
        toggle_dialog("I'm a placeholder NPC!", "I wobble a bit. I need gfx!", "Will this one day be you?");
    case IT_None:
        break;
    }
}

void on_dialog_confirm()
{
    tracef("on_dialog_confirm %d", g_currentInteractable?1:0);
    if (g_currentInteractable != 0)
    {
        on_interact(g_currentInteractable);
    }
}