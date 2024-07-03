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

extern const char* TEXTURE_FILES[TEXTURE_FILES_COUNT];

static inline void darken_pixel(uint32_t *pixel);

static inline uint32_t access_texture_pixel(int x, int y, int idx);

extern void dceiling();

extern void dwalls(
    int x,
    int y_low,
    int y_high,
    int line_height,
    offset_pt_t *ray_dir,
    dda_hit_t *hit);

#endif
