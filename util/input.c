#include "include/input.h"
#include "sokol_app.h"
#include "sokol_gfx.h"

bool keys[SAPP_MAX_KEYCODES] = {0};
bool prev_keys[SAPP_MAX_KEYCODES] = {0};

bool mouse_left_being_clicked = false;

float mouse_dx, mouse_dy;

bool is_key_down(sapp_keycode code) 
{
    return keys[code];
}

bool is_key_pressed(sapp_keycode code) 
{
    return keys[code] && !prev_keys[code];
}

void update_input(const sapp_event* ev) 
{
    // keyboard buttons
    if (ev->type == SAPP_EVENTTYPE_KEY_DOWN) 
    {
        keys[ev->key_code] = true;
    } 
    else if (ev->type == SAPP_EVENTTYPE_KEY_UP) 
    {
        keys[ev->key_code] = false;
    }

    // mouse movement
    if (ev->type == SAPP_EVENTTYPE_MOUSE_MOVE)
    {
        mouse_dx += ev->mouse_dx;
        mouse_dy += ev->mouse_dy;
    }

    // mouse buttons
    if (ev->type == SAPP_EVENTTYPE_MOUSE_DOWN) 
    {
        if (ev->mouse_button == SAPP_MOUSEBUTTON_LEFT) 
        {
            mouse_left_being_clicked = true;
        }
    } 
    else if (ev->type == SAPP_EVENTTYPE_MOUSE_UP) 
    {
        if (ev->mouse_button == SAPP_MOUSEBUTTON_LEFT) 
        {
            mouse_left_being_clicked = false;
        }
    }
}

void reset_input_states(void)
{
    // copy current keys to previous keys before the next frame starts
    for (int i = 0; i < SAPP_MAX_KEYCODES; i++) 
    {
        prev_keys[i] = keys[i];
    }
    
    // reset mouse deltas
    mouse_dx = 0;
    mouse_dy = 0;
}