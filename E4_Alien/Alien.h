//
//  Alien.h
//
//  Created by Jonas Willén on 2021-03-29.
//
#ifndef Alien_h
#define Alien_h

#include <stdio.h>

typedef struct Alien_type *Alien;

int getAlienPositionX(Alien a);
int getAlienPositionY(Alien a);
Alien createAlien(int x, int y);
void setAlienPositionY(Alien a, int y);
void setY(Alien a, int y);
int getAlienWidth();
int getAlienHeight();
int getAlienFrame(Alien a);
void AlienTick(Alien a);

#endif /* Alien_h */

