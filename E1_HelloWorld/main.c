#include <SDL.h>
#include <stdio.h>
#include <stdbool.h>

int main()
{
    if(SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("Failed to initialize the SDL2 library\n");
        return -1;
    }

    SDL_Window *window = SDL_CreateWindow("Hello World 2", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, 0);

    if(!window)
    {
        printf("Failed to create window\n");
        return -1;
    }

    SDL_Surface *window_surface = SDL_GetWindowSurface(window);

    if(!window_surface)
    {
        printf("Failed to get the surface from the window\n");
        return -1;
    }

    SDL_Surface *image = SDL_LoadBMP("hello_world.bmp");

    if(!image)
    {
        printf("Failed to load image\n");
        return -1;
    }

    bool keep_window_open = true;
    while(keep_window_open)
    {
        SDL_Event e;
        while(SDL_PollEvent(&e) > 0)
        {
            switch(e.type)
            {
            case SDL_QUIT:
                keep_window_open = false;
                break;
            }

            SDL_BlitSurface(image, NULL, window_surface, NULL);
            SDL_UpdateWindowSurface(window);
        }
    }

    SDL_FreeSurface(window_surface);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;

    

 
}
