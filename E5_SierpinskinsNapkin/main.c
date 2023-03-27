//
//  SierpinskinsNapkin.c
//  SierpinskinsNapkin
//
//  Created by Jonas Willénon 2022-04-04.
//

#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>

bool init(SDL_Renderer **gRenderer);

int main(int argc, char* args[])
{
    SDL_Event e;
    SDL_Renderer *gRenderer = NULL;
    SDL_Point points[8000] ={0};
    int choice;
    int count = 3;
    double x;
    double y;
    srand( (unsigned)time( NULL ));
    points[0].x = 500;
    points[0].y = 200;
    points[1].x = 200;
    points[1].y = 800;
    points[2].x = 800;
    points[2].y = 800;
   
    bool quit = false;
    
   
    if (init(&gRenderer)) {
        printf("worked\n");
    }
    

    choice = rand() % 2;
    points[count].x = points[choice].x;
    points[count].y = points[choice].y;
    
    SDL_RenderPresent(gRenderer);
    
    // Game loop - 1. Game Event 2. Game Logic 3. Render Game
    while (!quit ) {
        
        // Game event
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }
        }

        
        // Game logic use ATD 
        choice = rand() % 3;
        
        //printf("x: %d y: %d -- x: %d y: %d\n", points[choice].x, points[choice].y, points[count].x, points[count].y);
        if (points[count].x > points[choice].x){
            points[count+1].x = points[choice].x + (points[count].x-points[choice].x)/2;
        }else{
            points[count+1].x = points[count].x + (points[choice].x-points[count].x)/2;
        }
        
        if (points[count].y > points[choice].y){
            points[count+1].y = points[choice].y + (points[count].y-points[choice].y)/2;
        }else{
            points[count+1].y = points[count].y + (points[choice].y-points[count].y)/2;
        }
        
        count += 1;
    
        //printf("x: %d y: %d\n", points[count].x, points[count].y);
                            
        
        // Game renderer
        SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(gRenderer);
        SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0x00);
        SDL_RenderDrawPoints(gRenderer, points, count);
        SDL_RenderPresent(gRenderer);
        
        if(count == 8000){
            points[0].x = 500;
            points[0].y = 200;
            points[1].x = 200;
            points[1].y = 800;
            points[2].x = 800;
            points[2].y = 800;
            count = 3;
        }
    }
    
    return 0;
}



bool init(SDL_Renderer **gRenderer){
  bool test = true;
    SDL_Window  *gWindow = NULL;
    SDL_Init(SDL_INIT_VIDEO);
    gWindow = SDL_CreateWindow("Sierpinski's Napkin", SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED, 1000, 1000, SDL_WINDOW_SHOWN);
    if(gWindow == NULL){
        printf("Fungerar ej\n");
        test = false;
    }
    *gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED| SDL_RENDERER_PRESENTVSYNC);
    if(gRenderer == NULL){
        printf("Fungerar ej\n");
        test = false;
    }
    return test;
    
}



