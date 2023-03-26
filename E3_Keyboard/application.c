#include <SDL.h>
#include <stdio.h>
#include <stdbool.h>
#include "application.h"
#include "ball.h"

#define PUBLIC /* empty */
#define PRIVATE static

struct Application_type{
    SDL_Window  *window;
    SDL_Surface *window_surface;
    SDL_Event    window_event;
    Ball        ballOne;
    Ball        ballTwo;
};

PRIVATE void update(Application theApp, double delta_time);
PRIVATE void draw(Application theApp);

PUBLIC Application createApplication(){
    Application s = malloc(sizeof(struct Application_type));
    if(SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("Failed to initialize the SDL2 library\n");
    }

    s->window= SDL_CreateWindow("SDL2 Window",
                                          SDL_WINDOWPOS_CENTERED,
                                          SDL_WINDOWPOS_CENTERED,
                                          640, 480,
                                          0);

    if(!s->window)
    {
        printf("Failed to create window\n");
    }

   s->window_surface = SDL_GetWindowSurface(s->window);

    if(!s->window_surface)
    {
        printf("Failed to get the surface from the window\n"); 
    }

    s->ballOne = createBall(45, 45, 1);
    s->ballTwo = createBall(100, 100, 2);

    return s;

}

PUBLIC void applicationUpdate(Application theApp){
    bool keep_window_open = true;
    while(keep_window_open)
    {
        while(SDL_PollEvent(&theApp->window_event) > 0)
        {
            SDL_Event test = theApp->window_event;
            ballEventHandler(theApp->ballOne, theApp->window_event);
            switch(theApp->window_event.type)
            {
                case SDL_QUIT:
                    keep_window_open = false;
                    break;
            }
        }
        
        update(theApp, 10.0/60.0);
        draw(theApp);
    }
}

PRIVATE void update(Application theApp, double delta_time){
    ballUpdate(theApp->ballTwo, delta_time);
}

PRIVATE void draw(Application theApp)
{
    SDL_FillRect(theApp->window_surface, NULL, SDL_MapRGB(theApp->window_surface->format, 0, 0, 0));
    ballDraw(theApp->ballOne, theApp->window_surface);
    ballDraw(theApp->ballTwo, theApp->window_surface);
    SDL_UpdateWindowSurface(theApp->window);
}

PUBLIC void destoryApplication(Application theApp){
    SDL_FreeSurface(theApp->window_surface);
    SDL_DestroyWindow(theApp->window);
}

