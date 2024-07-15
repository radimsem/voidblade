#include <SDL2/SDL_events.h>
#include <SDL2/SDL_scancode.h>

#include "vb_movement.h"
#include "vb_input.h"

void handle_keys(state_t *state) {
    SDL_PumpEvents();

    if (state->keys[SDL_SCANCODE_W]) {
        move(&state->pos, &state->dir, state->speed.move, FORWARD);
    }
    if (state->keys[SDL_SCANCODE_S]) {
        move(&state->pos, &state->dir, state->speed.move, BACKWARD);
    }

    if (state->keys[SDL_SCANCODE_A]) {
        rotate(&state->dir, -state->speed.rot);
        rotate(&state->plane, -state->speed.rot);
    }
    if (state->keys[SDL_SCANCODE_D]) {
        rotate(&state->dir, +state->speed.rot);
        rotate(&state->plane, +state->speed.rot);
    }
}
