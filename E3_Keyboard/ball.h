#ifndef ball_h
#define ball_h


typedef struct Ball_type *Ball;

Ball createBall();
void ballUpdate(Ball theBall, double delta_time);
void ballDraw(Ball theBall, SDL_Surface *window_surface);
void ballEventHandler(Ball theBall, SDL_Event const e);

#endif
