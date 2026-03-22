#include "smart_pong_app.h"

#include <stdbool.h>
#include <stdint.h>

#include "edgeai_config.h"

#include "game/game.h"
#include "game/render.h"
#include "platform/display_hal.h"
#include "platform/input_hal.h"
#include "platform/time_hal.h"
#include "sw_render.h"

void smart_pong_app_start(void)
{
    time_hal_init();

    if (!display_hal_init())
    {
        for (;;) {}
    }

    display_hal_fill(0x0000u);

    input_hal_t input;
    (void)input_hal_init(&input);

    pong_game_t game;
    game_init(&game);

    render_state_t render;
    render_init(&render);

    const uint32_t frame_us = 1000000u / (uint32_t)EDGEAI_FIXED_FPS;
    const float dt = 1.0f / (float)EDGEAI_FIXED_FPS;

    for (;;)
    {
        uint32_t start = time_hal_cycles();

        platform_input_t in;
        input_hal_poll(&input, &in);

        game_step(&game, &in, dt);
        render_draw_frame(&render, &game);

        uint32_t elapsed_us = time_hal_elapsed_us(start);
        if (elapsed_us < frame_us)
        {
            time_hal_delay_us(frame_us - elapsed_us);
        }
    }
}
