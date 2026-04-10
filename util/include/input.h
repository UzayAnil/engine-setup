#pragma once
#include "sokol_app.h"
#include <stdbool.h>

#define UPKEY SAPP_KEYCODE_W
#define DOWNKEY SAPP_KEYCODE_S
#define LEFTKEY SAPP_KEYCODE_A
#define RIGHTKEY SAPP_KEYCODE_D

// mouse
extern float mouse_dx, mouse_dy;

// store all keys
extern bool keys[SAPP_MAX_KEYCODES];
extern bool prev_keys[SAPP_MAX_KEYCODES];

extern bool mouse_left_being_clicked;

// check continuous press
bool is_key_down(sapp_keycode code);

// check single press
bool is_key_pressed(sapp_keycode code); 

void update_input(const sapp_event* e);

// sets prev keys to current keys, and resets mouse deltas
void reset_input_states(void);