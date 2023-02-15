#include "wasm4.h"
#include "input.h"

uint8_t g_gamepad = 0;
uint8_t g_gamepad_prev = 0;

void input_update_early()
{
    g_gamepad = *GAMEPAD1;
}

void input_update_late()
{
    g_gamepad_prev = *GAMEPAD1;
}

bool button_held(u8 btn)
{
    return (g_gamepad & btn) != 0;
}

bool button_up(u8 btn)
{
    return (g_gamepad & btn) == 0;
}

//  Pressed this frame
bool button_newly_pressed(u8 btn)
{
    return ((g_gamepad & btn) != 0) && ((g_gamepad_prev & btn) == 0);
}

//  Released this frame
bool button_newly_released(u8 btn)
{
    return ((g_gamepad & btn) == 0) && ((g_gamepad_prev & btn) != 0);
}
