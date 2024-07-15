#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_keyboard.h>
#include <SDL2/SDL_video.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_pixels.h>

#include "vb_math.h"
#include "vb_state.h"
#include "vb_input.h"
#include "vb_render.h"
#include "vb_texture.h"

static state_t state;

int main() {
    ASSERT(!SDL_Init(SDL_INIT_VIDEO),
            "SDL failed to initialize: %s",
            SDL_GetError());

    state.window = SDL_CreateWindow(
        "VoidBlade",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        SCREEN_WIDTH,
        SCREEN_HEIGHT,
        0
    );
    ASSERT(state.window, "failed to create SDL window: %s", SDL_GetError());

    state.renderer = SDL_CreateRenderer(
        state.window,
        -1,
        SDL_RENDERER_ACCELERATED
    );
    ASSERT(state.renderer, "failed to create SDL renderer: %s", SDL_GetError());

    state.texture = SDL_CreateTexture(
        state.renderer,
        SDL_PIXELFORMAT_BGR888,
        SDL_TEXTUREACCESS_STREAMING,
        SCREEN_WIDTH,
        SCREEN_HEIGHT
    );
    ASSERT(state.texture, "failed to create SDL texture: %s", SDL_GetError());

    char texture_path[TEXTURE_FILENAME_SIZE];
    for (int i = 0; i < NUM_TEXTURE_FILES; i++) {
        snprintf(texture_path, TEXTURE_FILENAME_SIZE,
                "%s/%s", RESOURCE_DIR, TEXTURE_FILES[i]);

        state.surfaces[i] = IMG_Load(texture_path);
        ASSERT(state.surfaces[i], "failed to create SDL surface from image %s: %s", TEXTURE_FILES[i], SDL_GetError());
    }

    state.keys = SDL_GetKeyboardState(NULL);
    ASSERT(state.keys, "failed to get SDL keyboard state");

    state.pos.x = 4.5f;
    state.pos.y = 2.5f;

    state.dir.x = 1.0f;
    state.dir.y = 0.1f;

    // normalizing the direction vector
    normalize(&state.dir);

    // setting up FOV to 66° (great for this style render)
    state.plane.x = 0.0f;
    state.plane.y = 0.66f;

    state.speed.rot = 3.0f * 0.0025f;
    state.speed.move = 3.0f * 0.0025f;

    state.quit = false;

    while (!state.quit) {
        SDL_Event event;

        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    state.quit = true;
                    break;
            }
        }

        handle_keys(&state);

        // clear the pixel buffer for new render
        memset(state.pixels, 0, sizeof(state.pixels));

        render(&state);

        SDL_UpdateTexture(
            state.texture,
            NULL,
            state.pixels,
            SCREEN_WIDTH * 4
        );
        SDL_RenderCopyEx(
            state.renderer,
            state.texture,
            NULL,
            NULL,
            0.0,
            NULL,
            SDL_FLIP_VERTICAL
        );
        SDL_RenderPresent(state.renderer);
    }

    SDL_DestroyTexture(state.texture);
    SDL_DestroyRenderer(state.renderer);
    SDL_DestroyWindow(state.window);

    SDL_Quit();

    return 0;
}
