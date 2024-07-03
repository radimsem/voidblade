#include <stdint.h>
#include <stdbool.h>

#include <SDL2/SDL_video.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_surface.h>

#include "vb_macros.h"
#include "vb_types.h"

#ifndef __VB_STATE__
#define __VB_STATE__

typedef struct {
    float rot, move;
} speed_t;

static struct {
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Texture *texture;
    SDL_Surface *surfaces[TEXTURE_FILES_COUNT];

    uint32_t pixels[SCREEN_WIDTH * SCREEN_HEIGHT];

    offset_pt_t pos, dir, plane;
    speed_t speed;

    const uint8_t *keys;
    bool quit;
} state_s;

#endif
