#include "vec2.h"

#define PUBLIC /* empty */
#define PRIVATE static



PUBLIC Vec2 createVec2(double x, double y){
    Vec2 v = malloc(sizeof(struct Vec2_type));
    v->x = x;
    v->y = y;
    return v;
}




