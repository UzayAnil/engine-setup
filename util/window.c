#include "sokol_app.h"
#include "sokol_time.h"
#include "sokol_gfx.h"
#include "sokol_glue.h"
#include "sokol_log.h"
#include "include/input.h"

#include <stdio.h>

float WIDTH, HEIGHT;

void init_window(void)
{
    WIDTH = (float)sapp_width();
    HEIGHT = (float)sapp_height();

    sapp_lock_mouse(true);
    sapp_show_mouse(false);

    sg_setup(&(sg_desc)
    {
        .logger.func = slog_func,
        .environment = sglue_environment(),
    });

    stm_setup();
}

void event_window(const sapp_event* e)
{
    update_input(e);
}

void window_begin_pass(void)
{
    sg_begin_pass(&(sg_pass)
    {
        .action = 
        {
            .colors[0].clear_value = {0.08f, 0.08f, 0.08f, 1.0f},
            .colors[0].load_action = SG_LOADACTION_CLEAR,
            .depth.load_action = SG_LOADACTION_CLEAR,
            .depth.clear_value = 1.0f
        },
        .swapchain = sglue_swapchain(),
    });
}

void window_end_pass(void)
{
    sg_end_pass();
    sg_commit();
}

void end_program(void)
{
    sg_shutdown();
}