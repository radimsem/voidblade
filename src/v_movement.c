#include <math.h>

#include "v_types.h"
#include "v_map.h"

#include "v_movement.h"

void rotate(offset_pt_t *v, float rot) {
    float _x = v->x;
    v->x = (v->x * cos(rot)) - (v->y * sin(rot));
    v->y = (_x * sin(rot)) + (v->y * cos(rot));
}

void move(offset_pt_t *pos, offset_pt_t *dir, float speed, move_t type) {
    offset_pt_t move;

    switch (type) {
        case FORWARD:
            move.x = pos->x + dir->x * speed;
            move.y = pos->y + dir->y * speed;
            break;
        case BACKWARD:
            move.x = pos->x - dir->x * speed;
            move.y = pos->y - dir->y * speed;
            break;
    }

    tile_pt_t map_pos = {
        (int) move.x,
        (int) move.y
    };

    if (map_pos.x < 0 ||
        map_pos.x >= MAP_SIZE ||
        map_pos.y < 0 ||
        map_pos.y >= MAP_SIZE ||
        MAP_DATA[(map_pos.y * MAP_SIZE) + map_pos.x] > 0)
    {
        return;
    }

    *pos = move;
}
