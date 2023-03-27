#include <SDL.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include <stdbool.h>
#include "main.h"
#include "application.h"
#include "ball.h"
#include "vec2.h"
#include "paddle.h"
#include "playerScore.h"


struct Application_type{
    SDL_Window  *window;
    SDL_Surface *window_surface;
    SDL_Renderer *renderer;
    SDL_Event    window_event;
    TTF_Font    *scoreFont;
    Ball        theBall;
    Paddle      paddleOne;
    Paddle      paddleTwo;
    PlayerScore playerOneScore;
    PlayerScore playerTwoScore;
};

PRIVATE void update(Application theApp, double delta_time);
PRIVATE void draw(Application theApp);

PUBLIC Application createApplication(){
    Application s = malloc(sizeof(struct Application_type));
    if(SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("Failed to initialize the SDL2 library\n");
    }
    if(TTF_Init() == 0){
        printf("Success to initialize the SDL_ttf library\n");
    }


    s->window= SDL_CreateWindow("Pong", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    s->renderer = SDL_CreateRenderer(s->window, -1, 0);
    s->window_surface = SDL_GetWindowSurface(s->window);

    s->scoreFont = TTF_OpenFont("DejaVuSansMono.ttf", 40);
    s->playerOneScore = createPlayerScore(createVec2(WINDOW_WIDTH / 4, 20), s->renderer, s->scoreFont);
    s->playerTwoScore = createPlayerScore(createVec2(3 * WINDOW_WIDTH / 4, 20), s->renderer, s->scoreFont);


    Vec2 v = createVec2((WINDOW_WIDTH / 2.0f) - (BALL_WIDTH / 2.0f), (WINDOW_HEIGHT / 2.0f) - (BALL_WIDTH / 2.0f));
    s->theBall = createBall(v);

    s->paddleOne = createPaddle(createVec2(50.0f, (WINDOW_HEIGHT / 2.0f) - (PADDLE_HEIGHT / 2.0f)));
    s->paddleTwo = createPaddle(createVec2(WINDOW_WIDTH - 50.0f, (WINDOW_HEIGHT / 2.0f) - (PADDLE_HEIGHT / 2.0f)));


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
                case SDL_KEYDOWN:
                    if (theApp->window_event.key.keysym.sym == SDLK_ESCAPE)
			        {
				        keep_window_open = false;
			        }
			        else if (theApp->window_event.key.keysym.sym == SDLK_w)
			        {
                        updatePaddle(theApp->paddleOne, -2);
			        }
			        else if (theApp->window_event.key.keysym.sym == SDLK_s)
			        {
				        updatePaddle(theApp->paddleOne, 2);
			        }
			        else if (theApp->window_event.key.keysym.sym == SDLK_UP)
			        {
				        updatePaddle(theApp->paddleTwo, -2);
			        }
			        else if (theApp->window_event.key.keysym.sym == SDLK_DOWN)
			        {
				        updatePaddle(theApp->paddleTwo, 2);
			        }
                    break;
                case SDL_KEYUP:                 
                    if (theApp->window_event.key.keysym.sym == SDLK_w)
			        {
                        updatePaddle(theApp->paddleOne, 0);
			        }
			        else if (theApp->window_event.key.keysym.sym == SDLK_s)
			        {
				        updatePaddle(theApp->paddleOne, 0);
			        }
			        else if (theApp->window_event.key.keysym.sym == SDLK_UP)
			        {
				        updatePaddle(theApp->paddleTwo, 0);
			        }
			        else if (theApp->window_event.key.keysym.sym == SDLK_DOWN)
			        {
				        updatePaddle(theApp->paddleTwo, 0);
			        }
                    break;
            }

        }
        
        update(theApp, 10.0/60.0);
        updateBall(theApp->theBall, 1);

        // Check collisions ||
        if (checkCollisionBall(theApp->theBall, getPossitionPaddle(theApp->paddleTwo)) ||  checkCollisionBall(theApp->theBall, getPossitionPaddle(theApp->paddleOne)) )
        {
                printf("Have Collision\n");
	            handleCollisionBall(theApp->theBall);
        }

        draw(theApp);
    }
}

PRIVATE void update(Application theApp, double delta_time){
    updateBall(theApp->theBall, 1);
    
}

PRIVATE void draw(Application theApp)
{
    SDL_SetRenderDrawColor(theApp->renderer, 0x0, 0x0, 0x0, 0xFF);
	SDL_RenderClear(theApp->renderer);

    SDL_SetRenderDrawColor(theApp->renderer, 0xFF, 0xFF, 0xFF, 0xFF);

    for (int y = 0; y < WINDOW_HEIGHT; ++y)
    {
	    if (y % 5)
	    {
		    SDL_RenderDrawPoint(theApp->renderer, WINDOW_WIDTH / 2, y);
	    }
    }

    ballDraw(theApp->theBall, theApp->renderer);
    paddleDraw(theApp->paddleOne, theApp->renderer);
    paddleDraw(theApp->paddleTwo, theApp->renderer);

    playerScoreDraw(theApp->playerOneScore);
    playerScoreDraw(theApp->playerTwoScore);

	SDL_RenderPresent(theApp->renderer);
}

PUBLIC void destoryApplication(Application theApp){
    SDL_DestroyRenderer(theApp->renderer);
    SDL_FreeSurface(theApp->window_surface);
    SDL_DestroyWindow(theApp->window);
    TTF_CloseFont(theApp->scoreFont);
	TTF_Quit();
    SDL_Quit();
}

