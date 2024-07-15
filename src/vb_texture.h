#include <stdint.h>
#include <sys/types.h>

#include "vb_macros.h"
#include "vb_types.h"
#include "vb_render.h"

#ifndef __VB_TEXTURE__
#define __VB_TEXTURE__

#define TEXTURE_SIZE 64
#define DARK_TEXTURE_ACCESSOR 0x7f7f7f

#define TEXTURE_FILENAME_SIZE 32

#define VBT_WALLS 0
#define VBT_CEILING 1

extern const char* TEXTURE_FILES[NUM_TEXTURE_FILES];

void dceiling(state_t *state);

void dwalls(
    state_t *state,
    int x,
    int y_low,
    int y_high,
    int line_height,
    offset_pt_t *ray_dir,
    dda_hit_t *hit);

#endif
