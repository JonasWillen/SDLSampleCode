#include <SDL.h>
#include "ball.h"

#define PUBLIC /* empty */
#define PRIVATE static

struct Ball_type{
    SDL_Surface *m_image;
    SDL_Rect     m_position;
    double       m_x;
    double       m_y;
};

PUBLIC Ball createBall(int x, int y, int color){
    Ball b = malloc(sizeof(struct Ball_type));

    if(color == 1){
        b->m_image = SDL_LoadBMP("ball.bmp");
    }else{
        b->m_image = SDL_LoadBMP("ball2.bmp");
    }

    if(!b->m_image)
    {
        printf("Failed to load image\n");
    }

    b->m_position.x = x;
    b->m_position.y = y;
    b->m_position.w = 45;
    b->m_position.h = 45;
    b->m_x = x;
    b->m_y = y;
    return b;
}

PUBLIC void ballUpdate(Ball theBall, double delta_time){
    theBall->m_x = theBall->m_x + (1 * delta_time);
    theBall->m_position.x = theBall->m_x; 
}

PUBLIC void ballDraw(Ball theBall, SDL_Surface *window_surface){
    SDL_BlitSurface(theBall->m_image, NULL, window_surface, &theBall->m_position);
}

PUBLIC void ballEventHandler(Ball theBall, SDL_Event const e){
    if(e.type == SDL_KEYDOWN ){
        //Select surfaces based on key press
        switch( e.key.keysym.sym ){
            case SDLK_UP:
                printf("UP\n");
                theBall->m_position.y -= 4;   
                break;
            case SDLK_DOWN:
                theBall->m_position.y += 4;   
                break;
            case SDLK_LEFT:
                theBall->m_position.x -= 4;
                break;
            case SDLK_RIGHT:
                theBall->m_position.x += 4;
                break;
            default:
                break;
        }
    }

}
