//
//  spaceman.c
//
//  Created by Jonas Willén on 2021-03-29.
//

#include "spaceman.h"

#define PUBLIC /* empty */
#define PRIVATE static


PRIVATE int WIDTH = 16;
PRIVATE int HEIGHT = 16;

struct SpaceMan_type{
    int SPACEMAN_POSITION_X;
    int SPACEMAN_POSITION_Y;
    int SPACEMAN_FRAME;
    int speed;
};

PUBLIC SpaceMan createSpaceMan(int x, int y){
    SpaceMan s = malloc(sizeof(struct SpaceMan_type));
    s->SPACEMAN_POSITION_Y = y;
    s->SPACEMAN_POSITION_X = x;
    s->SPACEMAN_FRAME = 0;
    s->speed = 1;
    return s;
}



PUBLIC int getSpacemanHeight(){
    return HEIGHT;
}

PUBLIC int getSpacemanWidth(){
    return WIDTH;
}

PUBLIC void tick(int direction){
    
    
}

