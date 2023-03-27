#include <SDL.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include "vec2.h"

#ifndef playerScore_h
#define playerScore_h

typedef struct PlayerScore_type *PlayerScore;

PlayerScore createPlayerScore(Vec2 vec, SDL_Renderer* renderer, TTF_Font* font);
void playerScoreDraw(PlayerScore theScore);
void destroyPlayerScore(PlayerScore theScore);


#endif