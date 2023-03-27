#include <SDL_ttf.h>
#include "playerScore.h"
#include <SDL_ttf.h>

#define PUBLIC /* empty */
#define PRIVATE static

struct PlayerScore_type{
    SDL_Rect    m_position;
    SDL_Renderer* m_renderer;
	TTF_Font* m_font;
	SDL_Surface* m_surface;
	SDL_Texture* m_texture;
};

PUBLIC PlayerScore createPlayerScore(Vec2 vec, SDL_Renderer* renderer, TTF_Font* font){
    PlayerScore s = malloc(sizeof(struct PlayerScore_type));

    SDL_Color sdlCol = {0xFF, 0xFF, 0xFF, 0xFF};
    s->m_renderer = renderer;
    s->m_surface = TTF_RenderText_Solid(font, "0", sdlCol);
    s->m_texture = SDL_CreateTextureFromSurface(s->m_renderer, s->m_surface);

    int width, height;
    SDL_QueryTexture(s->m_texture, 0, 0, &width, &height);

    s->m_position.x = (int) vec->x;
    s->m_position.y = (int) vec->y;
    s->m_position.w = width;
    s->m_position.h = height;

    return s;
}

PUBLIC void destroyPlayerScore(PlayerScore theScore){
    SDL_FreeSurface(theScore->m_surface);
    SDL_DestroyTexture(theScore->m_texture);
}

PUBLIC void playerScoreDraw(PlayerScore theScore){
    SDL_RenderCopy(theScore->m_renderer, theScore->m_texture, 0, &theScore->m_position);
}