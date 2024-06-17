#include <stdbool.h>

#include <SDL2/SDL_video.h>
#include <SDL2/SDL_render.h>

#include "v_macros.h"
#include "v_types.h"

#ifndef __V_STATE__
#define __V_STATE__

typedef struct {
    float rot, move;
} speed_t;

static struct {
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Texture *texture;

    uint32_t pixels[SCREEN_WIDTH * SCREEN_HEIGHT];
    bool quit;

    offset_pt_t pos, dir, plane;
    speed_t speed;
} state_s;

#endif
