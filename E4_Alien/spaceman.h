//
//  spaceman.h
//
//  Created by Jonas Willén on 2021-03-29.
//

#ifndef spaceman_h
#define spaceman_h

#include <stdio.h>
#include <stdlib.h>

typedef struct SpaceMan_type *SpaceMan;

int getSpacemanPositionX(SpaceMan s);
int getSpacemanPositionY(SpaceMan s);
SpaceMan createSpaceMan(int x, int y);

#endif /* spaceman_h */



