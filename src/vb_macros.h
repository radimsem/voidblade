#include <stdio.h>

#ifndef __V_MACROS__
#define __V_MACROS__

#define ASSERT(_e, ...) if (!(_e)) { fprintf(stderr, __VA_ARGS__); exit(1); }

#define SCREEN_WIDTH 480
#define SCREEN_HEIGHT 360

#define CAMERA_HEIGHT SCREEN_HEIGHT / 2

#define RESOURCE_DIR "rc"
#define NUM_TEXTURE_FILES 2

#define NUM_SPRITES 11

#endif
