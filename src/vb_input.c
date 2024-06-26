#include <SDL2/SDL_scancode.h>

#include "vb_state.h"

#include "vb_movement.c"

#include "vb_input.h"

void handle_keys() {
    SDL_PumpEvents();

    if (state_s.keys[SDL_SCANCODE_W]) {
        move(&state_s.pos, &state_s.dir, state_s.speed.move, FORWARD);
    }
    if (state_s.keys[SDL_SCANCODE_S]) {
        move(&state_s.pos, &state_s.dir, state_s.speed.move, BACKWARD);
    }

    if (state_s.keys[SDL_SCANCODE_A]) {
        rotate(&state_s.dir, -state_s.speed.rot);
        rotate(&state_s.plane, -state_s.speed.rot);
    }
    if (state_s.keys[SDL_SCANCODE_D]) {
        rotate(&state_s.dir, +state_s.speed.rot);
        rotate(&state_s.plane, +state_s.speed.rot);
    }
}
