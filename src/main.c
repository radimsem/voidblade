#include <SDL2/SDL.h>
#include <SDL2/SDL_keyboard.h>
#include <SDL2/SDL_video.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_error.h>
#include <SDL2/SDL_keycode.h>

#include "vb_render.c"
#include "vb_input.c"

int main() {
    ASSERT(!SDL_Init(SDL_INIT_VIDEO),
            "SDL failed to initialize: %s",
            SDL_GetError());

    state_s.window = SDL_CreateWindow(
        "VoidBlade",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        SCREEN_WIDTH,
        SCREEN_HEIGHT,
        0
    );
    ASSERT(state_s.window, "failed to create SDL window: %s", SDL_GetError());

    state_s.renderer = SDL_CreateRenderer(
        state_s.window,
        -1,
        SDL_RENDERER_ACCELERATED
    );
    ASSERT(state_s.renderer, "failed to create SDL renderer: %s", SDL_GetError());

    state_s.texture = SDL_CreateTexture(
        state_s.renderer,
        SDL_PIXELFORMAT_BGR888,
        SDL_TEXTUREACCESS_STREAMING,
        SCREEN_WIDTH,
        SCREEN_HEIGHT
    );
    ASSERT(state_s.texture, "failed to create SDL texture: %s", SDL_GetError());

    state_s.pos.x = 4.5f;
    state_s.pos.y = 2.5f;

    state_s.dir.x = 1.0f;
    state_s.dir.y = 0.1f;

    normalize(&state_s.dir);

    state_s.plane.x = 0.0f;
    state_s.plane.y = 0.66f;

    state_s.speed.rot = 3.0f * 0.001f;
    state_s.speed.move = 3.0f * 0.001f;

    state_s.keys = SDL_GetKeyboardState(NULL);
    state_s.quit = false;

    while (!state_s.quit) {
        SDL_Event event;

        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    state_s.quit = true;
                    break;
            }
        }

        handle_keys();

        memset(state_s.pixels, 0, sizeof(state_s.pixels));
        render();

        SDL_UpdateTexture(
            state_s.texture,
            NULL,
            state_s.pixels,
            SCREEN_WIDTH * 4
        );
        SDL_RenderCopyEx(
            state_s.renderer,
            state_s.texture,
            NULL,
            NULL,
            0.0,
            NULL,
            SDL_FLIP_VERTICAL
        );
        SDL_RenderPresent(state_s.renderer);
    }

    SDL_DestroyTexture(state_s.texture);
    SDL_DestroyRenderer(state_s.renderer);
    SDL_DestroyWindow(state_s.window);

    SDL_Quit();

    return 0;
}
