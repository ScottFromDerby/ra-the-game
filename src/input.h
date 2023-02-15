#pragma once
#include "wasm4.h"

extern uint8_t g_gamepad;
extern uint8_t g_gamepad_prev;

extern bool button_held(u8 btn);
extern bool button_up(u8 btn);
extern bool button_newly_pressed(u8 btn);
extern bool button_newly_released(u8 btn);

extern void input_update_early();
extern void input_update_late();
