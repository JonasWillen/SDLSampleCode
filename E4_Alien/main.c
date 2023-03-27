//
//  main.c
//  SDLtesta
//
//  Created by Jonas Willén on 2021-03-29.
//
// #include <SDL2/SDL.h>
// #include <SDL2/SDL_image.h> 
//

#include <stdio.h>
#include <SDL.h>
#include <SDL_image.h> 
#include <stdbool.h>
#include "world.h"
#include "Alien.h"

#undef main

bool init(SDL_Renderer **gRenderer);
void loadMedia(SDL_Renderer *gRenderer, SDL_Texture **mSpaceman, SDL_Rect gSpriteClips[], SDL_Texture **mAlien, SDL_Rect gAlien[], SDL_Texture **mTiles, SDL_Rect gTiles[]);
void renderBackground(SDL_Renderer *gRenderer, SDL_Texture *mTile, SDL_Rect gTiles[]);

int main(int argc, char* args[])
{
    
    SDL_Event e;
    SDL_Renderer *gRenderer = NULL;
    bool quit = false;
    
    // Spaceman
    SDL_Texture *mSpaceman = NULL;
    SDL_Rect gSpriteClips[8];
    SDL_RendererFlip flip = SDL_FLIP_NONE;
    SDL_Rect possition;
    possition.y = 64;
    possition.x = 110;
    possition.h = 16;
    possition.w = 16;
    int frame = 6;
    
    // Alien 1 and 2
    SDL_Texture *mAlien = NULL;
    SDL_Rect gAlien[2];
    Alien a1;
    a1 = createAlien(41, 100);
    SDL_Rect a1possition = {getAlienPositionY(a1),getAlienPositionX(a1),15,15};
    
    Alien a2;
    a2 = createAlien(80, 100);
    SDL_Rect a2possition = {getAlienPositionY(a1),getAlienPositionX(a1),15,15};
   
    // Background
    SDL_Texture *mTiles = NULL;
    SDL_Rect gTiles[16];
   
    if (init(&gRenderer)) {
        printf("worked\n");
    }
    
    loadMedia(gRenderer, &mSpaceman, gSpriteClips, &mAlien, gAlien, &mTiles, gTiles);
    
    // Game loop - 1. Game Event 2. Game Logic 3. Render Game
    while (!quit) {
        
        // Game event
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }
            else if( e.type == SDL_KEYDOWN )
            {
                //Select surfaces based on key press
                switch( e.key.keysym.sym )
                {
                    case SDLK_UP:
                        printf("UP\n");
                        // should be in game logic
                        possition.y -= 2;
                        flip = SDL_FLIP_NONE;
                        if(frame == 4)
                            frame = 5;
                        else
                            frame = 4;
                        break;
                    case SDLK_DOWN:
                        possition.y += 2;
                        flip = SDL_FLIP_NONE;
                        if(frame == 0)
                            frame = 1;
                        else
                            frame = 0;
                        break;
                    case SDLK_LEFT:
                        possition.x -= 2;
                        flip = SDL_FLIP_HORIZONTAL;
                        if(frame == 2)
                            frame = 3;
                        else
                            frame = 2;
                        break;
                    case SDLK_RIGHT:
                        possition.x += 2;
                        flip = SDL_FLIP_NONE;
                        if(frame == 2)
                            frame = 3;
                        else
                            frame = 2;
                        break;
                    default:
                        
                        break;
                }
            }
            
        }
        
        // Game logic use ATD 
        AlienTick(a1);
        a1possition.x = getAlienPositionY(a1);
        a1possition.y = getAlienPositionX(a1);
        int foo = collidesWithImpassableTile(possition.x, possition.y);
        
        // Game renderer
        SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(gRenderer);
        renderBackground(gRenderer, mTiles, gTiles);
        SDL_RenderCopyEx(gRenderer, mSpaceman, &gSpriteClips[frame],&possition , 0, NULL, flip);
        SDL_RenderCopyEx(gRenderer, mAlien, &gAlien[getAlienFrame(a1)],&a1possition ,270, NULL, SDL_FLIP_NONE);
        SDL_RenderCopyEx(gRenderer, mAlien, &gAlien[getAlienFrame(a2)],&a2possition ,270, NULL, SDL_FLIP_NONE);
        SDL_RenderPresent(gRenderer);
    }
    
    return 0;
}

void renderBackground(SDL_Renderer *gRenderer, SDL_Texture *mTiles, SDL_Rect gTiles[]){
    
    SDL_Rect possition;
    possition.y = 0;
    possition.x = 0;
    possition.h = getTileHeight();
    possition.w = getTileWidth();
    
    for (int i = 0; i<getTileColumns(); i++) {
        for (int j = 0; j<getTileRows(); j++) {
            possition.y = i*getTileHeight();
            possition.x = j*getTileWidth();
            SDL_RenderCopyEx(gRenderer, mTiles, &gTiles[getTileGrid(i,j)],&possition , 0, NULL, SDL_FLIP_NONE);
        }
    }
    
}

void loadMedia(SDL_Renderer *gRenderer, SDL_Texture **mSpaceman, SDL_Rect gSpriteClips[], SDL_Texture **mAlien, SDL_Rect gAlien[], SDL_Texture **mTiles, SDL_Rect gTiles[]){
    
    SDL_Surface* gSpacemanSurface = IMG_Load("resources/SPACEMAN.PNG");
    *mSpaceman = SDL_CreateTextureFromSurface(gRenderer, gSpacemanSurface);
  
    
    gSpriteClips[ 0 ].x =   0;
    gSpriteClips[ 0 ].y =   0;
    gSpriteClips[ 0 ].w =  16;
    gSpriteClips[ 0 ].h = 16;
    
    gSpriteClips[ 1 ].x =  16;
    gSpriteClips[ 1 ].y =   0;
    gSpriteClips[ 1 ].w =  16;
    gSpriteClips[ 1 ].h = 16;
    
    gSpriteClips[ 2 ].x = 32;
    gSpriteClips[ 2 ].y =   0;
    gSpriteClips[ 2 ].w =  16;
    gSpriteClips[ 2 ].h = 16;
    
    gSpriteClips[ 3 ].x = 48;
    gSpriteClips[ 3 ].y =   0;
    gSpriteClips[ 3 ].w =  16;
    gSpriteClips[ 3 ].h = 16;
    
    gSpriteClips[ 4 ].x = 64;
    gSpriteClips[ 4 ].y =   0;
    gSpriteClips[ 4 ].w =  16;
    gSpriteClips[ 4 ].h = 16;
    
    gSpriteClips[ 5 ].x = 80;
    gSpriteClips[ 5 ].y =   0;
    gSpriteClips[ 5 ].w =  16;
    gSpriteClips[ 5 ].h = 16;
    
    gSpriteClips[ 6 ].x = 96;
    gSpriteClips[ 6 ].y =   0;
    gSpriteClips[ 6 ].w =  16;
    gSpriteClips[ 6 ].h = 16;
    
    gSpriteClips[ 7 ].x = 112;
    gSpriteClips[ 7 ].y =   0;
    gSpriteClips[ 7 ].w =  16;
    gSpriteClips[ 7 ].h = 16;
    
    
    SDL_Surface* gTilesSurface = IMG_Load("resources/TILES.PNG");
    *mTiles = SDL_CreateTextureFromSurface(gRenderer, gTilesSurface);
    for (int i = 0; i < 16; i++) {
        gTiles[i].x = i*getTileWidth();
        gTiles[i].y = 0;
        gTiles[i].w = getTileWidth();
        gTiles[i].h = getTileHeight();
    }
    
    SDL_Surface* gSAlien = IMG_Load("resources/ALIEN.PNG");
    *mAlien = SDL_CreateTextureFromSurface(gRenderer, gSAlien);
    gAlien[ 0 ].x = 0;
    gAlien[ 0 ].y = 0;
    gAlien[ 0 ].w = 15;
    gAlien[ 0 ].h = 15;
    
    gAlien[ 1 ].x = 15;
    gAlien[ 1 ].y = 0;
    gAlien[ 1 ].w = 15;
    gAlien[ 1 ].h = 15;
    
    
}


bool init(SDL_Renderer **gRenderer){
    bool test = true;
    SDL_Window  *gWindow = NULL;
    SDL_Init(SDL_INIT_VIDEO);
    gWindow = SDL_CreateWindow("SDL Test", SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED, 400, 300, SDL_WINDOW_SHOWN);
    if(gWindow == NULL){
        printf("Fungerar ej\n");
        test = false;
    }
    *gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED| SDL_RENDERER_PRESENTVSYNC);
    if(*gRenderer == NULL){
        printf("Fungerar ej\n");
        test = false;
    }
    return test;
    
}



