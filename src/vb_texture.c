#include <stdint.h>
#include <math.h>

#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_image.h>

#include "vb_state.h"

#include "vb_math.c"

#include "vb_texture.h"

const char *TEXTURE_FILE = "./res/walls.png";

extern void draw_texture_line(int x, int y_low, int y_high, int line_height, offset_pt_t *ray_dir, dda_hit_t *hit) {
    if (SDL_LockSurface(state_s.surface) < 0) {
        return;
    }

    float wall_x;
    switch (hit->side) {
        case HORIZONTAL:
            wall_x = state_s.pos.y + (hit->dist * ray_dir->y);
            break;
        case VERTICAL:
            wall_x = state_s.pos.x + (hit->dist * ray_dir->x);
            break;
    }
    wall_x -= floorf(wall_x);

    int texture_x = (float) TEXTURE_SIZE * wall_x;
    int texture_x_offset = TEXTURE_SIZE * (hit->value - 1);

    // adjusting the texture_x coordinate based on surface orientation and ray direction
    if ((hit->side == HORIZONTAL && ray_dir->x > 0) ||
        (hit->side == VERTICAL && ray_dir->y < 0))
    {
        texture_x = (TEXTURE_SIZE - 1) - texture_x;
    }

    float step = ((float) TEXTURE_SIZE) / line_height;
    float texture_pos = (y_low - ((float) SCREEN_HEIGHT / 2) + ((float) line_height / 2)) * step;

    for (int y = y_high; y >= y_low; y--) {
        int texture_y = min((int) texture_pos, TEXTURE_SIZE - 1);
        texture_pos += step;

        int texture_pixel_idx = (texture_y * state_s.surface->w) + (texture_x + texture_x_offset);
        uint32_t color = ((uint32_t*) state_s.surface->pixels)[texture_pixel_idx];

        if (hit->side == VERTICAL) {
            // darkening the texture pixel for vertical wall
            color = (color >> 1) & DARK_TEXTURE_ACCESSOR;
        }

        state_s.pixels[(y * SCREEN_WIDTH) + x] = color;
    }

    SDL_UnlockSurface(state_s.surface);
}
