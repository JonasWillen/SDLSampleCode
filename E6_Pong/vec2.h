#include <SDL.h>
#include <stdio.h>

#ifndef vec2_h
#define vec2_h

struct Vec2_type{
    double  x;
    double  y;
};

typedef struct Vec2_type *Vec2;



Vec2 createVec2(double x, double y);


#endif
