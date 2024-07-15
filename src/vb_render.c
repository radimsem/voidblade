#include "vb_macros.h"
#include "vb_types.h"
#include "vb_state.h"
#include "vb_map.h"
#include "vb_math.h"
#include "vb_texture.h"
#include "vb_render.h"

void render(state_t *state) {
    dceiling(state);

    for (int x = 0; x < SCREEN_WIDTH; x++) {
        // calculate the camera x coordinate in range of 1 and -1
        float cam_x = 2 * (x / (float) SCREEN_WIDTH) - 1;

        offset_pt_t ray_dir = {
            state->dir.x + state->plane.x * cam_x,
            state->dir.y + state->plane.y * cam_x,
        };

        tile_pt_t map_pos = {
            (int) state->pos.x,
            (int) state->pos.y
        };

        offset_pt_t delta_dist = {
            // avoiding to division by zero
            ray_dir.x == 0 ? INFINITY : fabsf(TILE_WIDTH / ray_dir.x),
            ray_dir.y == 0 ? INFINITY : fabsf(TILE_WIDTH / ray_dir.y)
        };

        offset_pt_t side_dist = {
            delta_dist.x * (ray_dir.x < 0 ? (state->pos.x - map_pos.x) : (map_pos.x + 1 - state->pos.x)),
            delta_dist.y * (ray_dir.y < 0 ? (state->pos.y - map_pos.y) : (map_pos.y + 1 - state->pos.y)),
        };

        // signing the ray direction coordinates to 1 or -1
        tile_pt_t step = {
            sign(ray_dir.x),
            sign(ray_dir.y)
        };

        dda_hit_t hit = { 0, 0 };

        while (hit.value == 0) {
            if (side_dist.x < side_dist.y) {
                side_dist.x += delta_dist.x;
                map_pos.x += step.x;
                hit.side = HORIZONTAL;
            } else {
                side_dist.y += delta_dist.y;
                map_pos.y += step.y;
                hit.side = VERTICAL;
            }

            // bound check for new tile coordinates
            ASSERT(map_pos.x >= 0 &&
                    map_pos.x < MAP_SIZE &&
                    map_pos.y >= 0 &&
                    map_pos.y < MAP_SIZE,
                    "DDA out of bounds: [%d, %d]",
                    map_pos.x,
                    map_pos.y);

            hit.value = MAP_DATA[(map_pos.y * MAP_SIZE) + map_pos.x];
        }

        hit.pos.x = state->pos.x + side_dist.x;
        hit.pos.y = state->pos.y + side_dist.y;

        switch (hit.side) {
            case HORIZONTAL:
                hit.dist = side_dist.x - delta_dist.x;
                break;
            case VERTICAL: {
                hit.dist = side_dist.y - delta_dist.y;
                break;
            }
        }
        state->zbuf[x] = hit.dist;

        int
            h = SCREEN_HEIGHT / hit.dist,
            y0 = max((SCREEN_HEIGHT / 2) - (h / 2), 0),
            y1 = min((SCREEN_HEIGHT / 2) + (h / 2), SCREEN_HEIGHT - 1);

        dwalls(state, x, y0, y1, h, &ray_dir, &hit);
    }
}
