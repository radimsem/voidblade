#include "v_types.h"

#ifndef __V_MOVEMENT__
#define __V_MOVEMENT__

typedef enum {
    FORWARD,
    BACKWARD
} move_t;

void rotate(offset_pt_t *v, float rot);

void move(offset_pt_t *pos, offset_pt_t *dir, float speed, move_t mov);

#endif
