#pragma once
#include "sokol_app.h"

extern void init_window(void);
extern void event_window(const sapp_event* e);
extern void window_begin_pass(void);
extern void window_end_pass(void);
extern void end_program(void);