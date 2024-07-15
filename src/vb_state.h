#include <stdbool.h>
#include <SDL2/SDL.h>

#include "vb_macros.h"
#include "vb_types.h"

#ifndef __VB_STATE__
#define __VB_STATE__

typedef struct {
    float rot, move;
} speed_t;

typedef struct {
    int order[NUM_SPRITES];
    float dists[NUM_SPRITES];
} sprites_t;

typedef struct {
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Texture *texture;
    SDL_Surface *surfaces[NUM_TEXTURE_FILES];

    uint32_t pixels[SCREEN_WIDTH * SCREEN_HEIGHT];
    float zbuf[SCREEN_WIDTH];

    offset_pt_t pos, dir, plane;
    speed_t speed;
    sprites_t sprites;

    const uint8_t *keys;
    bool quit;
} state_t;

#endif
