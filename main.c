#include <stdio.h>

#include "sokol_gfx.h"
#include "sokol_app.h"
#include "sokol_log.h"
#include "sokol_time.h"

#include "util/include/window.h"
#include "util/include/general.h"
#include "util/include/input.h"

// globals

// fps cap
float dt = 0;
bool fpscap = true;
uint64_t last_time = 0;
double target_fps = 240.0;
float t = 0;

void init(void)
{
    init_window();
}

void frame_cb(void)
{
    // dt
    dt = (float)sapp_frame_duration();

    // print ft/fps every .5 sec
    t += dt;
    if (t >= 0.5f)
    {
        printf("MS: %.2f | FPS: %.2f \n", 1000.0f * dt, 1.0f / dt);
        t = 0.0f;
    }

    // quit on esc
    if (is_key_pressed(SAPP_KEYCODE_ESCAPE)) sapp_quit();
    
    // begin render
    window_begin_pass();

    window_end_pass();
    reset_input_states();

    // fps cap
    if (fpscap && target_fps > 0) 
    {
        double target_dt = 1.0 / target_fps;  
        while (stm_sec(stm_since(last_time)) < target_dt) {}
    }
    last_time = stm_now();
}

void cleanup(void)
{
    end_program();
}

sapp_desc sokol_main(int argc, char* argv[])
{
    return (sapp_desc) 
    {
        .width = WIDTH,
        .height = HEIGHT,
        .fullscreen = true,
        .init_cb = init,
        .frame_cb = frame_cb,
        // in sokol_app.h so vsync isnt forced on
        // comment this line
        // res.swap_interval = _sapp_def(res.swap_interval, 1);
        .swap_interval = 0, 
        .event_cb = event_window,
        .cleanup_cb = cleanup,
        .logger.func = slog_func,
    };
}