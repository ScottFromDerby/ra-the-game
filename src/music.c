#include "wasm4.h"

#include "music.h"
#include "tools.h"
#include "gfx.h"

const u32 SMALL_NOTE_DURATION = 5;

// https://pages.mtu.edu/~suits/notefreqs.html

const u32 C1 = 33;
const u32 Db1 = 35;
const u32 D1 = 37;
const u32 Eb1 = 39;
const u32 E1 = 41;
const u32 F1 = 44;
const u32 Gb1 = 46;
const u32 G1 = 49;
const u32 Ab1 = 52;
const u32 A1 = 55;
const u32 Bb1 = 58;
const u32 B1 = 61;

const u32 C2 = 65;
const u32 Db2 = 69;
const u32 D2 = 73;
const u32 Eb2 = 78;
const u32 E2 = 82;
const u32 F2 = 87;
const u32 Gb2 = 93;
const u32 G2 = 98;
const u32 Ab2 = 104;
const u32 A2 = 110;
const u32 Bb2 = 117;
const u32 B2 = 123;

const u32 C3 = 131;
const u32 Db3 = 139;
const u32 D3 = 147;
const u32 Eb3 = 156;
const u32 E3 = 165;
const u32 F3 = 175;
const u32 Gb3 = 185;
const u32 G3 = 196;
const u32 Ab3 = 208;
const u32 A3 = 220;
const u32 Bb3 = 233;
const u32 B3 = 247;

const u32 C4 = 262;
const u32 Db4 = 277;
const u32 D4 = 294;
const u32 Eb4 = 311;
const u32 E4 = 330;
const u32 F4 = 349;
const u32 Gb4 = 370;
const u32 G4 = 392;
const u32 Ab4 = 415;
const u32 A4 = 440;
const u32 Bb4 = 466;
const u32 B4 = 494;

const u32 C5 = 523;
const u32 Db5 = 554;
const u32 D5 = 587;
const u32 Eb5 = 622;
const u32 E5 = 659;
const u32 F5 = 698;
const u32 Gb5 = 740;
const u32 G5 = 784;
const u32 Ab5 = 830;
const u32 A5 = 880;
const u32 Bb5 = 932;
const u32 B5 = 988;

const u32 C6 = 1047;
const u32 Db6 = 1109;
const u32 D6 = 1175;
const u32 Eb6 = 1245;
const u32 E6 = 1318;
const u32 F6 = 1397;
const u32 Gb6 = 1480;
const u32 G6 = 1568;
const u32 Ab6 = 1661;
const u32 A6 = 1760;
const u32 Bb6 = 1865;
const u32 B6 = 1976;

const u32 bass_music[] = {C2, G2, F2, G2, Eb2, G2, F2, G2,
                          C2, G2, F2, G2, Eb2, G2, F2, G2,
                          C2, Ab2, G2, Ab2, F2, Ab2, G2, Ab2,
                          C2, Ab2, G2, Ab2, F2, Ab2, G2, Ab2,
                          C2, Ab2, G2, Ab2, F2, Ab2, G2, Ab2,
                          C2, Ab2, G2, Ab2, F2, Ab2, G2, Ab2,
                          C2, Eb2, D2, Eb2, G2, Eb2, D2, Eb2,
                          C2, Eb2, D2, Eb2, G2, Eb2, D2, Eb2,

                          C2, C3, Bb2, C3, Ab2, C3, Bb2, C3,
                          C2, C3, Bb2, C3, Ab2, C3, Bb2, C3,
                          C2, A2, G2, A2, Gb2, A2, G2, A2,
                          C2, A2, G2, A2, Gb2, A2, G2, A2,
                          Bb1, Bb2, A2, Bb2, G2, Bb2, A2, Bb2,
                          Bb1, Bb2, A2, Bb2, G2, Bb2, A2, Bb2,
                          Bb1, G2, F2, G2, E2, G2, F2, G2,
                          Bb1, G2, F2, G2, E2, G2, F2, G2
                        };
const u32 bass_musicLen = sizeof(bass_music) / sizeof(bass_music[0]);
const u32 bass_duration[] = {2, 2, 2, 2, 2, 2, 2, 2,
                             2, 2, 2, 2, 2, 2, 2, 2,
                             2, 2, 2, 2, 2, 2, 2, 2,
                             2, 2, 2, 2, 2, 2, 2, 2,
                             2, 2, 2, 2, 2, 2, 2, 2,
                             2, 2, 2, 2, 2, 2, 2, 2,
                             2, 2, 2, 2, 2, 2, 2, 2,
                             2, 2, 2, 2, 2, 2, 2, 2,

                             2, 2, 2, 2, 2, 2, 2, 2,
                             2, 2, 2, 2, 2, 2, 2, 2,
                             2, 2, 2, 2, 2, 2, 2, 2,
                             2, 2, 2, 2, 2, 2, 2, 2,
                             2, 2, 2, 2, 2, 2, 2, 2,
                             2, 2, 2, 2, 2, 2, 2, 2,
                             2, 2, 2, 2, 2, 2, 2, 2,
                             2, 2, 2, 2, 2, 2, 2, 2};

// const u32 accp_music[] = { 0, Gb4, Gb4, G4, Gb4,
// 								G4, Gb4, E4, A4,
// 								Gb4, Gb4, G4, Gb4,
// 								B4, B4, A4, 0, A4, A4, D4, 0 };
// const u32 accp_musicLen = sizeof(accp_music) / sizeof(accp_music[0]);
// const u32 accp_duration[] = { 4, 8, 8, 8, 8,
// 									8, 8, 8, 8,
// 									8, 8, 8, 4,
// 									4, 4, 4, 4, 4, 4, 4, 4 };

const u32 lead_music[] = {C6, Eb5, D5, Eb5, C5, Eb5, D5, Eb5,
                          C6, Eb5, D5, Eb5, C5, Eb5, D5, Eb5,
                          Ab5, F5, E5, F5, C5, F5, E5, F5,
                          Ab5, F5, E5, F5, C5, F5, E5, F5,
                          B5, F5, Eb5, F5, D5, F5, Eb5, F5,
                          B5, F5, Eb5, F5, D5, F5, Eb5, F5,
                          C6, G5, F5, G5, Eb5, G5, F5, G5,
                          C6, G5, F5, G5, Eb5, G5, F5, G5,

                          Eb6, Ab5, G5, Ab5, Eb5, Ab5, G5, Ab5, 
                          Eb6, Ab5, G5, Ab5, Eb5, Ab5, G5, Ab5, 
                          D6, Gb5, E5, Gb5, D5, Gb5, E5, Gb5, 
                          D6, Gb5, E5, Gb5, D5, Gb5, E5, Gb5, 
                          D6, G5, Gb5, G5, D5, G5, Gb5, G5, 
                          D6, G5, Gb5, G5, D5, G5, Gb5, G5, 
                          C6, E5, D5, E5, C5, E5, D5, E5, 
                          C6, E5, D5, E5, C5, E5, D5, E5, 
                          };
const u32 lead_musicLen = sizeof(lead_music) / sizeof(lead_music[0]);
const u32 lead_duration[] = {2, 2, 2, 2, 2, 2, 2, 2,
                             2, 2, 2, 2, 2, 2, 2, 2,
                             2, 2, 2, 2, 2, 2, 2, 2,
                             2, 2, 2, 2, 2, 2, 2, 2,
                             2, 2, 2, 2, 2, 2, 2, 2,
                             2, 2, 2, 2, 2, 2, 2, 2,
                             2, 2, 2, 2, 2, 2, 2, 2,
                             2, 2, 2, 2, 2, 2, 2, 2,

                             2, 2, 2, 2, 2, 2, 2, 2,
                             2, 2, 2, 2, 2, 2, 2, 2,
                             2, 2, 2, 2, 2, 2, 2, 2,
                             2, 2, 2, 2, 2, 2, 2, 2,
                             2, 2, 2, 2, 2, 2, 2, 2,
                             2, 2, 2, 2, 2, 2, 2, 2,
                             2, 2, 2, 2, 2, 2, 2, 2,
                             2, 2, 2, 2, 2, 2, 2, 2};

u32 lead_nextFreq = lead_musicLen - 1;
u32 lead_delayLeft = 1;
// u32 accp_nextFreq = accp_musicLen-1;
// u32 accp_delayLeft = 1;
u32 bass_nextFreq = bass_musicLen - 1;
u32 bass_delayLeft = 1;

u32 perc_delayLeft = (SMALL_NOTE_DURATION * 4);

void music_tick(bool bIncludeLead)
{
    // static u32 nextFreq = g_uTicks / SMALL_NOTE_DURATION % musicLen;

    // Gfx::drawval(lead_nextFreq, 1, 50, 0x21);
    // Gfx::drawval(lead_music[lead_nextFreq], 1, 57, 0x21);
    // Gfx::drawval(accp_nextFreq, 1, 64, 0x21);
    // Gfx::drawval(accp_music[accp_nextFreq], 1, 71, 0x21);
    // Gfx::drawval(bass_nextFreq, 1, 78, 0x21);
    // Gfx::drawval(bass_music[bass_nextFreq], 1, 85, 0x21);
    lead_delayLeft--;
    if (lead_delayLeft == 0)
    {
        lead_nextFreq = (lead_nextFreq + 1) % lead_musicLen;
        lead_delayLeft = lead_duration[lead_nextFreq] * SMALL_NOTE_DURATION;
        const u32 a = 2;
        const u32 d = 3;
        const u32 s = 2;
        const u32 r = 1;
        if (lead_music[lead_nextFreq] != 0)
        {
            // const u32 NOTE_BLEND = 36;
            const u32 NOTE_BLEND = 5;
            if (bIncludeLead)
            {
                tone(((lead_music[lead_nextFreq] - NOTE_BLEND)) | lead_music[lead_nextFreq] << 16, a | d << 8 | s << 16 | r << 24, 20, TONE_PULSE2);
            }
        }
    }
    bass_delayLeft--;
    if (bass_delayLeft == 0)
    {
        bass_nextFreq = (bass_nextFreq + 1) % bass_musicLen;
        bass_delayLeft = bass_duration[bass_nextFreq] * SMALL_NOTE_DURATION;
        const u32 a = 6;
        const u32 d = 6;
        const u32 s = 10;
        const u32 r = 5;
        if (bass_music[bass_nextFreq] != 0)
        {
            tone(bass_music[bass_nextFreq], a | d << 8 | s << 16 | r << 24, 30, TONE_TRIANGLE);
        }
    }
    // accp_delayLeft--;
    // if (accp_delayLeft == 0)
    //{
    //	accp_nextFreq = (accp_nextFreq + 1) % accp_musicLen;
    //	accp_delayLeft = accp_duration[accp_nextFreq] * SMALL_NOTE_DURATION;
    //	const u32 a = 4;
    //	const u32 d = 2;
    //	const u32 s = 9;
    //	const u32 r = 6;
    //	const u32 sustain_vol = 20;
    //	const u32 attack_peak = 30;
    //	if (accp_music[accp_nextFreq] != 0)
    //	{
    //		//tone(accp_music[accp_nextFreq], a | d << 8 | s << 16 | r << 24, sustain_vol | attack_peak << 8, TONE_PULSE1 | TONE_MODE4);
    //	}
    // }
    perc_delayLeft--;
    if (perc_delayLeft == 0)
    {
        perc_delayLeft = SMALL_NOTE_DURATION * 8;

        const u32 a = 2;
        const u32 d = 4;
        const u32 s = 4;
        const u32 r = 0;
        const u32 sustain_vol = 15;
        const u32 attack_peak = 15;
        // tone(440, a | d << 8 | s << 16 | r << 24, sustain_vol | attack_peak << 8, TONE_NOISE);
    }
}