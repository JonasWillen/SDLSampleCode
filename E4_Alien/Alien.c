//
//  Alien.c
//
//  Created by Jonas Willén on 2021-03-29.
//


#include <stdlib.h>
#include "Alien.h"


#define PUBLIC /* empty */
#define PRIVATE static

PRIVATE int ALIEN_WIDTH = 15;
PRIVATE int ALIEN_HEIGHT = 15;

struct Alien_type{
    int ALIEN_POSITION_X;
    int ALIEN_POSITION_Y;
    int ALIEN_FRAME;
    int slow;
};

PUBLIC Alien createAlien(int x, int y){
    Alien s = malloc(sizeof(struct Alien_type));
    s->ALIEN_POSITION_Y = y;
    s->ALIEN_POSITION_X = x;
    s->ALIEN_FRAME = 0;
    s->slow = 1;
    return s;
}

void setY(Alien a, int y){
    a->ALIEN_POSITION_Y = y;
}


PUBLIC void setAlienPositionY(Alien a, int y){
    a->ALIEN_POSITION_Y = y;
}

PUBLIC int getAlienPositionX(Alien a){
    return a->ALIEN_POSITION_X;
}


PUBLIC int getAlienPositionY(Alien a){
    return a->ALIEN_POSITION_Y;
}

PUBLIC int getAlienWidth(){
    return ALIEN_WIDTH;
}

PUBLIC int getAlienHeight(){
    return ALIEN_HEIGHT;
}

PUBLIC int getAlienFrame(Alien a){
    return a->ALIEN_FRAME;
}


PUBLIC void AlienTick(Alien a){
    if(a->slow == 5){
        (a->ALIEN_POSITION_Y)++;
        a->ALIEN_FRAME = 0;
    }else if(a->slow == 10){
        (a->ALIEN_POSITION_Y)++;
        a->ALIEN_FRAME = 1;
        a->slow = 0;
    }
    (a->slow)++;

}
