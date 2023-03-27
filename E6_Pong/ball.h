#include <SDL.h>
#include <stdio.h>
#include "vec2.h"

#ifndef ball_h
#define ball_h

typedef struct Ball_type *Ball;

Ball createBall(Vec2 aVec);

void updateBall(Ball theBall, int dt);
bool checkCollisionBall(Ball theBall, SDL_Rect aRec);
void handleCollisionBall(Ball theBall);
void ballDraw(Ball theBall, SDL_Renderer* renderer);


#endif
