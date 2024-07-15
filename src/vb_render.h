#include <stdint.h>

#include "vb_state.h"
#include "vb_types.h"

#ifndef __VB_RENDER__
#define __VB_RENDER__

typedef enum {
    HORIZONTAL,
    VERTICAL
} tile_side_t;

typedef struct {
    int value;
    tile_side_t side;
    offset_pt_t pos;
    float dist;
} dda_hit_t;

void render(state_t *state);

#endif
