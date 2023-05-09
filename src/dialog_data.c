#include "dialog_data.h"

// InstructionDialog = "To devs! Dlg opcodes! Use #hash to change to alt colour and ~tilde to go back to regular text. @At symbol forces a new line."
const uint16_t DLGTEXT_InstructionDialog[] = {0, 1, 2, 3, 4, 5, 6, 7, 6, 8, 9, 10, 11, 6, 12, 13, 6, 14, 15, 16, 17, 18, 19, 20, 21, (uint16_t)-1 };

// WelcomeNPC1 = "Hi there! Welcome to our village. It is #great~ here!"
const uint16_t DLGTEXT_WelcomeNPC1[] = {22, 23, 24, 6, 25, 26, 27, 28, 29, 30, (uint16_t)-1 };

// WelcomeNPC2 = "Do you like music? Try poking my #spiky record player~."
const uint16_t DLGTEXT_WelcomeNPC2[] = {31, 32, 33, 34, 35, 36, 37, 38, 39, 40, (uint16_t)-1 };

// WelcomeNPCImpatient = "Why are you still talking to me? Go look around the village."
const uint16_t DLGTEXT_WelcomeNPCImpatient[] = {41, 42, 32, 43, 44, 6, 45, 46, 47, 48, 49, 26, (uint16_t)-1 };

// WelcomeNPCEnjoyingMusic = "Yes! Love this song! It reminds me of this kid I once knew. Looks a lot like you actually..."
const uint16_t DLGTEXT_WelcomeNPCEnjoyingMusic[] = {50, 51, 52, 53, 27, 54, 55, 56, 52, 57, 58, 59, 60, 61, 19, 62, 33, 32, 63, (uint16_t)-1 };

// GrumpyNPC = "I don't want you in our village. Go away. It is not #great~ here."
const uint16_t DLGTEXT_GrumpyNPC[] = {58, 64, 65, 32, 66, 25, 26, 46, 67, 27, 28, 68, 29, 69, (uint16_t)-1 };

// ShieldMan = "I'm the guy to hand out #shields~, but I ran out. I wonder if you could go get one?"
const uint16_t DLGTEXT_ShieldMan[] = {70, 49, 71, 6, 72, 73, 74, 75, 58, 76, 77, 58, 78, 79, 32, 80, 12, 81, 82, (uint16_t)-1 };

// ShieldMan2 = "There aren't any #yes~ or #no~ prompts yet. Sorry about that."
const uint16_t DLGTEXT_ShieldMan2[] = {83, 84, 85, 86, 87, 88, 89, 90, 91, 92, 93, (uint16_t)-1 };

// ShieldMan3 = "Maybe you could help? Come to the #RetroAchievements~ #Discord~ and come help add them!"
const uint16_t DLGTEXT_ShieldMan3[] = {94, 32, 80, 95, 96, 6, 49, 97, 98, 10, 99, 100, 101, 102, (uint16_t)-1 };

// ShieldMan4 = "My creator, the amazing #Scott~ has decided that I have to have a really long dialog prompt full of lots and lots of words to test out my..."
const uint16_t DLGTEXT_ShieldMan4[] = {103, 104, 49, 105, 106, 107, 108, 109, 58, 110, 6, 110, 19, 111, 112, 113, 114, 115, 56, 116, 10, 116, 56, 117, 6, 118, 73, 119, (uint16_t)-1 };

// ShieldMan5 = "ability to speak really long bits of information. Will it work? #Sort of.~@4 lines of dialog is plenty and will work anyway I'm sure."
const uint16_t DLGTEXT_ShieldMan5[] = {120, 6, 121, 111, 112, 122, 56, 123, 124, 125, 126, 127, 128, 129, 56, 113, 28, 130, 10, 131, 132, 133, 70, 134, (uint16_t)-1 };

// MusicBoxOn = "You switched it #on~."
const uint16_t DLGTEXT_MusicBoxOn[] = {135, 136, 125, 137, (uint16_t)-1 };

// MusicBoxOff = "You switched it #off~."
const uint16_t DLGTEXT_MusicBoxOff[] = {135, 136, 125, 138, (uint16_t)-1 };

// NPCPlaceholder1 = "I'm a placeholder NPC 1! I wobble a bit. I need gfx! Will this #one day be you~?"
const uint16_t DLGTEXT_NPCPlaceholder1[] = {70, 19, 139, 140, 141, 58, 142, 19, 143, 58, 144, 145, 124, 52, 146, 147, 148, 149, (uint16_t)-1 };

// NPCPlaceholder2 = "I'm a placeholder NPC 2! I wobble a bit. I need gfx! Will this #one day be you~?"
const uint16_t DLGTEXT_NPCPlaceholder2[] = {70, 19, 139, 140, 150, 58, 142, 19, 143, 58, 144, 145, 124, 52, 146, 147, 148, 149, (uint16_t)-1 };

// NPCPlaceholder3 = "I'm a placeholder NPC 3! I wobble a bit. I need gfx! Will this #one day be you~?"
const uint16_t DLGTEXT_NPCPlaceholder3[] = {70, 19, 139, 140, 151, 58, 142, 19, 143, 58, 144, 145, 124, 52, 146, 147, 148, 149, (uint16_t)-1 };

// NPCPlaceholder4 = "I'm a placeholder NPC 4! I wobble a bit. I need gfx! Will this #one day be you~?"
const uint16_t DLGTEXT_NPCPlaceholder4[] = {70, 19, 139, 140, 152, 58, 142, 19, 143, 58, 144, 145, 124, 52, 146, 147, 148, 149, (uint16_t)-1 };

const char* DLG_IDLOOKUP[] = { "To", "devs!", "Dlg", "opcodes!", "Use", "#hash", "to", "change", "alt", "colour", "and", "~tilde", "go", "back", "regular", "text.", "@At", "symbol", "forces", "a", "new", "line.", "Hi", "there!", "Welcome", "our", "village.", "It", "is", "#great~", "here!", "Do", "you", "like", "music?", "Try", "poking", "my", "#spiky", "record", "player~.", "Why", "are", "still", "talking", "me?", "Go", "look", "around", "the", "Yes!", "Love", "this", "song!", "reminds", "me", "of", "kid", "I", "once", "knew.", "Looks", "lot", "actually...", "don't", "want", "in", "away.", "not", "here.", "I'm", "guy", "hand", "out", "#shields~,", "but", "ran", "out.", "wonder", "if", "could", "get", "one?", "There", "aren't", "any", "#yes~", "or", "#no~", "prompts", "yet.", "Sorry", "about", "that.", "Maybe", "help?", "Come", "#RetroAchievements~", "#Discord~", "come", "help", "add", "them!", "My", "creator,", "amazing", "#Scott~", "has", "decided", "that", "have", "really", "long", "dialog", "prompt", "full", "lots", "words", "test", "my...", "ability", "speak", "bits", "information.", "Will", "it", "work?", "#Sort", "of.~@4", "lines", "plenty", "will", "work", "anyway", "sure.", "You", "switched", "#on~.", "#off~.", "placeholder", "NPC", "1!", "wobble", "bit.", "need", "gfx!", "#one", "day", "be", "you~?", "2!", "3!", "4!", };