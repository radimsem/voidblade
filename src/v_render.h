#include <stdint.h>

#ifndef __V_RENDER__
#define __V_RENDER__

typedef enum {
    HORIZONTAL,
    VERTICAL
} tile_side_t;

typedef struct {
    int value;
    tile_side_t side;
} dda_hit_t;

static void verline(int x, int y0, int y1, uint32_t color);

void render(void);

#endif
