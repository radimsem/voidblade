#include <math.h>

#include <SDL2/SDL_image.h>

#include "vb_state.h"
#include "vb_types.h"

#include "vb_math.c"

#include "vb_texture.h"

const char *TEXTURE_FILES[TEXTURE_FILES_COUNT] = {
    "walls.png",
    "ceiling.png"
};

static inline void darken_pixel(uint32_t *pixel) {
    *pixel = (*pixel >> 1) & DARK_TEXTURE_ACCESSOR;
}

static inline uint32_t access_texture_pixel(int x, int y, int idx) {
    // texture buffer bound check
    if (idx >= TEXTURE_FILES_COUNT ||
        x < 0 ||
        x >= state_s.surfaces[idx]->w ||
        y < 0 ||
        y >= state_s.surfaces[idx]->h)
    {
        return 0;
    }
    return ((uint32_t*) state_s.surfaces[idx]->pixels)[(y * state_s.surfaces[idx]->w) + x];
}

// draw floor and ceiling textures
extern void dceiling() {
    offset_pt_t ray_min = {
        state_s.dir.x - state_s.plane.x,
        state_s.dir.y - state_s.plane.y
    };
    offset_pt_t ray_max = {
        state_s.dir.x + state_s.plane.x,
        state_s.dir.y + state_s.plane.y
    };

    for (int y = 0; y < SCREEN_HEIGHT; y++) {
        // curr y position compared to the center of the screen
        float horizon = y - ((float) CAMERA_HEIGHT);

        float row_dist = ((float) CAMERA_HEIGHT) / horizon;
        offset_pt_t step = {
            row_dist * (ray_max.x - ray_min.x) / SCREEN_WIDTH,
            row_dist * (ray_max.y - ray_min.y) / SCREEN_WIDTH,
        };

        offset_pt_t ceiling_offset = {
            state_s.pos.x + (row_dist * ray_min.x),
            state_s.pos.y + (row_dist * ray_min.y),
        };

        for (int x = 0; x < SCREEN_WIDTH; x++) {
            tile_pt_t ceiling_tile = {
                (int) ceiling_offset.x,
                (int) ceiling_offset.y
            };
            tile_pt_t texture_pos = {
                (int) min(TEXTURE_SIZE * (ceiling_offset.x - ceiling_tile.x), TEXTURE_SIZE - 1),
                (int) min(TEXTURE_SIZE * (ceiling_offset.y - ceiling_tile.y), TEXTURE_SIZE - 1),
            };

            ceiling_offset.x += step.x;
            ceiling_offset.y += step.y;

            uint32_t pixel;
            // ceiling
            pixel = access_texture_pixel(texture_pos.x + TEXTURE_SIZE, texture_pos.y, VBT_CEILING);
            darken_pixel(&pixel);
            state_s.pixels[(y * SCREEN_WIDTH) + x] = pixel;

            // floor
            pixel = access_texture_pixel(texture_pos.x, texture_pos.y, VBT_CEILING);
            darken_pixel(&pixel);
            // symetric render from ceiling
            state_s.pixels[(((SCREEN_HEIGHT - 1) - y) * SCREEN_WIDTH) + x] = pixel;
        }
    }
}

// draw textures for walls that were hit by DDA
extern void dwalls(
    int x,
    int y_low,
    int y_high,
    int line_height,
    offset_pt_t *ray_dir,
    dda_hit_t *hit)
{
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

        uint32_t pixel = access_texture_pixel((texture_x + texture_x_offset), texture_y, VBT_WALLS);
        if (hit->side == VERTICAL) {
            darken_pixel(&pixel);
        }

        state_s.pixels[(y * SCREEN_WIDTH) + x] = pixel;
    }
}
