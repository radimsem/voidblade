#include <math.h>

#include "v_types.h"
#include "v_map.h"

#include "v_movement.h"

void rotate(offset_pt_t *v, float rot) {
    float _x = v->x;
    v->x = (v->x * cos(rot)) - (v->y * sin(rot));
    v->y = (_x * sin(rot)) + (v->y * cos(rot));
}

void move(offset_pt_t *pos, offset_pt_t *dir, float speed, move_t mov) {
    float _x = pos->x, _y = pos->y;

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

    tile_pt_t map_pos = {
        (int) pos->x,
        (int) pos->y
    };
    if (map_pos.x < 0 ||
        map_pos.x >= MAP_SIZE ||
        map_pos.y < 0 ||
        map_pos.y >= MAP_SIZE ||
        MAP_DATA[(map_pos.y * MAP_SIZE) + map_pos.x] > 0)
    {
        pos->x = _x;
        pos->y = _y;
    }
}
