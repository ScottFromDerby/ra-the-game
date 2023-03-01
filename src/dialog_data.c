#include "dialog_data.h"

// WelcomeNPC1 = "Hi there! Welcome to our village. It is #great~ here!"
const uint16_t DLGTEXT_WelcomeNPC1[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, (uint16_t)-1 };

// WelcomeNPC2 = "Do you like music? Try poking my #spiky record player~."
const uint16_t DLGTEXT_WelcomeNPC2[] = {10, 11, 12, 13, 14, 15, 16, 17, 18, 19, (uint16_t)-1 };

// WelcomeNPCImpatient = "Why are you still talking to me? Go look around the village."
const uint16_t DLGTEXT_WelcomeNPCImpatient[] = {20, 21, 11, 22, 23, 3, 24, 25, 26, 27, 28, 5, (uint16_t)-1 };

// WelcomeNPCEnjoyingMusic = "Yes! Love this song! It reminds me of this kid I once knew. Looks a lot like you actually..."
const uint16_t DLGTEXT_WelcomeNPCEnjoyingMusic[] = {29, 30, 31, 32, 6, 33, 34, 35, 31, 36, 37, 38, 39, 40, 41, 42, 12, 11, 43, (uint16_t)-1 };

// GrumpyNPC = "I don't want you in our village. Go away. It is not #great~ here."
const uint16_t DLGTEXT_GrumpyNPC[] = {37, 44, 45, 11, 46, 4, 5, 25, 47, 6, 7, 48, 8, 49, (uint16_t)-1 };

// ShieldMan = "I'm the guy to hand out #shields~, but I ran out. I wonder if you could go get one?"
const uint16_t DLGTEXT_ShieldMan[] = {50, 28, 51, 3, 52, 53, 54, 55, 37, 56, 57, 37, 58, 59, 11, 60, 61, 62, 63, (uint16_t)-1 };

// ShieldMan2 = "There aren't any #yes~ or #no~ prompts yet. Sorry."
const uint16_t DLGTEXT_ShieldMan2[] = {64, 65, 66, 67, 68, 69, 70, 71, 72, (uint16_t)-1 };

// ShieldMan3 = "Maybe you could help? Come to the #RetroAchievements~ #Discord~ and come help add them"
const uint16_t DLGTEXT_ShieldMan3[] = {73, 11, 60, 74, 75, 3, 28, 76, 77, 78, 79, 80, 81, 82, (uint16_t)-1 };

// MusicBoxOn = "You switched it #on~."
const uint16_t DLGTEXT_MusicBoxOn[] = {83, 84, 85, 86, (uint16_t)-1 };

// MusicBoxOff = "You switched it #off~."
const uint16_t DLGTEXT_MusicBoxOff[] = {83, 84, 85, 87, (uint16_t)-1 };

// NPCPlaceholder1 = "I'm a placeholder NPC 1! I wobble a bit. I need gfx! Will this #one day be you~?"
const uint16_t DLGTEXT_NPCPlaceholder1[] = {50, 41, 88, 89, 90, 37, 91, 41, 92, 37, 93, 94, 95, 31, 96, 97, 98, 99, (uint16_t)-1 };

// NPCPlaceholder2 = "I'm a placeholder NPC 2! I wobble a bit. I need gfx! Will this #one day be you~?"
const uint16_t DLGTEXT_NPCPlaceholder2[] = {50, 41, 88, 89, 100, 37, 91, 41, 92, 37, 93, 94, 95, 31, 96, 97, 98, 99, (uint16_t)-1 };

// NPCPlaceholder3 = "I'm a placeholder NPC 3! I wobble a bit. I need gfx! Will this #one day be you~?"
const uint16_t DLGTEXT_NPCPlaceholder3[] = {50, 41, 88, 89, 101, 37, 91, 41, 92, 37, 93, 94, 95, 31, 96, 97, 98, 99, (uint16_t)-1 };

// NPCPlaceholder4 = "I'm a placeholder NPC 4! I wobble a bit. I need gfx! Will this #one day be you~?"
const uint16_t DLGTEXT_NPCPlaceholder4[] = {50, 41, 88, 89, 102, 37, 91, 41, 92, 37, 93, 94, 95, 31, 96, 97, 98, 99, (uint16_t)-1 };

const char* DLG_IDLOOKUP[] = { "Hi", "there!", "Welcome", "to", "our", "village.", "It", "is", "#great~", "here!", "Do", "you", "like", "music?", "Try", "poking", "my", "#spiky", "record", "player~.", "Why", "are", "still", "talking", "me?", "Go", "look", "around", "the", "Yes!", "Love", "this", "song!", "reminds", "me", "of", "kid", "I", "once", "knew.", "Looks", "a", "lot", "actually...", "don't", "want", "in", "away.", "not", "here.", "I'm", "guy", "hand", "out", "#shields~,", "but", "ran", "out.", "wonder", "if", "could", "go", "get", "one?", "There", "aren't", "any", "#yes~", "or", "#no~", "prompts", "yet.", "Sorry.", "Maybe", "help?", "Come", "#RetroAchievements~", "#Discord~", "and", "come", "help", "add", "them", "You", "switched", "it", "#on~.", "#off~.", "placeholder", "NPC", "1!", "wobble", "bit.", "need", "gfx!", "Will", "#one", "day", "be", "you~?", "2!", "3!", "4!", };