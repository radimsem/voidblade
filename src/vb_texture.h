#include "vb_types.h"
#include "vb_render.h"

#ifndef __VB_TEXTURE__
#define __VB_TEXTURE__

#define TEXTURE_SIZE 64
#define DARK_TEXTURE_ACCESSOR 0x7f7f7f

#define TEXTURE_FILE "./rc/walls.png"

extern void draw_texture_line(
    int x,
    int y_low,
    int y_high,
    int line_height,
    offset_pt_t *ray_dir,
    dda_hit_t *hit);

#endif
