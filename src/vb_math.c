#include <math.h>

#include "vb_math.h"

int sign(float x) {
    return x < 0 ? -1 : x > 0 ? 1 : 0;
}

int min(int a, int b) {
    return a < b ? a : b;
}

int max(int a, int b) {
    return a > b ? a : b;
}

void normalize(offset_pt_t *v) {
    float length = sqrtf((v->x * v->x) + (v->y * v->y));
    v->x = v->x / length;
    v->y = v->y / length;
}
