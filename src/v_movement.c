#include <math.h>

#include "v_movement.h"

void rotate(offset_pt_t *v, float rot) {
    float _x = v->x;
    v->x = (v->x * cos(rot)) - (v->y * sin(rot));
    v->y = (_x * sin(rot)) + (v->y * cos(rot));
}

void move(offset_pt_t *pos, offset_pt_t *dir, float speed, move_t mov) {
    switch (mov) {
        case FORWARD:
            pos->x += dir->x * speed;
            pos->y += dir->y * speed;
            break;
        case BACKWARD:
            pos->x -= dir->x * speed;
            pos->y -= dir->y * speed;
            break;
    }
}
