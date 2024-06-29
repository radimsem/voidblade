#include "vb_macros.h"
#include "vb_types.h"
#include "vb_state.h"
#include "vb_map.h"

#include "vb_math.c"
#include "vb_texture.c"

#include "vb_render.h"

static void verline(int x, int y0, int y1, uint32_t color) {
    for (int y = y0; y <= y1; y++) {
        state_s.pixels[(y * SCREEN_WIDTH) + x] = color;
    }
}

void render() {
    for (int x = 0; x < SCREEN_WIDTH; x++) {
        float cam_x = 2 * (x / (float) SCREEN_WIDTH) - 1;

        offset_pt_t ray_dir = {
            state_s.dir.x + state_s.plane.x * cam_x,
            state_s.dir.y + state_s.plane.y * cam_x,
        };

        tile_pt_t map_pos = {
            (int) state_s.pos.x,
            (int) state_s.pos.y
        };

        offset_pt_t delta_dist = {
            ray_dir.x == 0 ? INFINITY : fabsf(TILE_WIDTH / ray_dir.x),
            ray_dir.y == 0 ? INFINITY : fabsf(TILE_WIDTH / ray_dir.y)
        };

        offset_pt_t side_dist = {
            delta_dist.x * (ray_dir.x < 0 ? (state_s.pos.x - map_pos.x) : (map_pos.x + 1 - state_s.pos.x)),
            delta_dist.y * (ray_dir.y < 0 ? (state_s.pos.y - map_pos.y) : (map_pos.y + 1 - state_s.pos.y)),
        };

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

            ASSERT(map_pos.x >= 0 &&
                    map_pos.x < MAP_SIZE &&
                    map_pos.y >= 0 &&
                    map_pos.y < MAP_SIZE,
                    "DDA out of bounds: [%d, %d]",
                    map_pos.x,
                    map_pos.y);

            hit.value = MAP_DATA[(map_pos.y * MAP_SIZE) + map_pos.x];
        }

        hit.pos.x = state_s.pos.x + side_dist.x;
        hit.pos.y = state_s.pos.y + side_dist.y;

        switch (hit.side) {
            case HORIZONTAL:
                hit.dist = side_dist.x - delta_dist.x;
                break;
            case VERTICAL: {
                hit.dist = side_dist.y - delta_dist.y;
                break;
            }
        }

        int
            h = SCREEN_HEIGHT / hit.dist,
            y0 = max((SCREEN_HEIGHT / 2) - (h / 2), 0),
            y1 = min((SCREEN_HEIGHT / 2) + (h / 2), SCREEN_HEIGHT - 1);

        verline(x, 0, y0, 0xFF202020);
        draw_texture_line(x, y0, y1, h, &ray_dir, &hit);
        verline(x, y1, SCREEN_HEIGHT - 1, 0xFF505050);
    }
}
