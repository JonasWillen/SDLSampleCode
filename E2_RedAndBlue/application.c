#include <SDL.h>
#include <stdio.h>
#include <stdbool.h>
#include "application.h"

#define PUBLIC /* empty */
#define PRIVATE static

struct Application_type{
    SDL_Window  *window;
    SDL_Surface *window_surface;
    SDL_Event    window_event;
    SDL_Surface *image1;
    SDL_Rect     image_position1;
    SDL_Surface *image2;
    SDL_Rect     image_position2;
    double       x1;
    double       x2;
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

    s->image1 = SDL_LoadBMP("ball.bmp");

    if(!s->image1)
    {
        printf("Failed to load image\n");
    }

    s->image_position1.x = 0;
    s->image_position1.y = 0;
    s->image_position1.w = 45;
    s->image_position1.h = 45;
    s->x1 = 0.0;

    s->image2 = SDL_LoadBMP("ball2.bmp");

    if(!s->image2)
    {
        printf("Failed to load image\n");
    }

    s->image_position2.x = 100;
    s->image_position2.y = 100;
    s->image_position2.w = 45;
    s->image_position2.h = 45;
    s->x2 = 100.0;


    return s;

}

PUBLIC void applicationUpdate(Application theApp){
    bool keep_window_open = true;
    while(keep_window_open)
    {
       
        while(SDL_PollEvent(&theApp->window_event) > 0)
        {
            switch(theApp->window_event.type)
            {
                case SDL_QUIT:
                    keep_window_open = false;
                    break;
            }
        }
        
        update(theApp, 30.0/60.0);
        
        draw(theApp);
    }
}

PRIVATE void update(Application theApp, double delta_time){
    theApp->x1 = theApp->x1 + (1 * delta_time);
    theApp->image_position1.x = theApp->x1; 
    theApp->x2 = theApp->x2 + (1 * delta_time);
    theApp->image_position2.x = theApp->x2; 
}

PRIVATE void draw(Application theApp)
{
    SDL_FillRect(theApp->window_surface, NULL, SDL_MapRGB(theApp->window_surface->format, 0, 0, 0));
    SDL_BlitSurface(theApp->image1, NULL, theApp->window_surface, &theApp->image_position1);
    SDL_BlitSurface(theApp->image2, NULL, theApp->window_surface, &theApp->image_position2);
    SDL_UpdateWindowSurface(theApp->window);
}

PUBLIC void destoryApplication(Application theApp){
    SDL_FreeSurface(theApp->window_surface);
    SDL_DestroyWindow(theApp->window);
    SDL_Quit();
}

