#include <stdbool.h>
#include "ball.h"

#define PUBLIC /* empty */
#define PRIVATE static

const int BALL_WIDTH2 = 15;
const int BALL_HEIGHT2 = 15;
const float BALLSPEED = 1.0f;

enum CollisionType{
	None,
	Top,
	Middle,
	Bottom,
    Left,
    Right
};

struct Contact
{
	enum CollisionType type;
	float penetration;
};
typedef struct Contact SContact;


struct Ball_type{
    SDL_Rect    m_rec;
    SContact    m_contact; 
    Vec2        m_velocity;
    Vec2        m_position;
 
};

PUBLIC Ball createBall(Vec2 vec){
    Ball b = malloc(sizeof(struct Ball_type));

    b->m_rec.x = (int) vec->x;
    b->m_rec.y = (int) vec->y;
    b->m_rec.w = BALL_WIDTH2;
    b->m_rec.h = BALL_HEIGHT2;

    b->m_position = vec;
    b->m_velocity = createVec2(1.0f, 0.0f);

    return b;
}

PUBLIC void updateBall(Ball theBall, int dt){
    theBall->m_position->y = theBall->m_position->y + theBall->m_velocity->y * dt;
    theBall->m_position->x = theBall->m_position->x + theBall->m_velocity->x * dt;
}

PUBLIC bool checkCollisionBall(Ball theBall, SDL_Rect aRec){
    int ballLeft = theBall->m_rec.x;
    int ballRight = theBall->m_rec.x + theBall->m_rec.w;
    int ballTop = theBall->m_rec.y;
    int ballBottom = theBall->m_rec.y + theBall->m_rec.h;

    int objectLeft = aRec.x;
    int objectRight = aRec.x + aRec.w;
    int objectTop = aRec.y;
    int objectBottom = aRec.y + aRec.h;

    if (ballLeft >= objectRight){
       
		return false;
	} else if (ballRight <= objectLeft){
		return false;
	} else if (ballTop >= objectBottom){
		return false;
	} else if (ballBottom <= objectTop){
		return false;
	}

    float paddleRangeUpper = objectBottom - (2.0f * 100 / 3.0f);
	float paddleRangeMiddle = objectBottom - (100 / 3.0f);

    if (theBall->m_velocity->x < 0)
	{
		// Left paddle
		theBall->m_contact.penetration = objectRight - ballLeft + 5;
         printf("Left %f \n", theBall->m_contact.penetration );

	}else if (theBall->m_velocity->x > 0)
	{
		// Right paddle
		theBall->m_contact.type = objectLeft - ballRight - 5;
        printf("Right %f \n", theBall->m_contact.penetration );
    }

    if ((ballBottom > objectTop)
	    && (ballBottom < paddleRangeUpper))
	{
		theBall->m_contact.type = Top;
	}
	else if ((ballBottom > paddleRangeUpper)
	     && (ballBottom < paddleRangeMiddle))
	{
		theBall->m_contact.type = Middle;
	}
	else
	{
		theBall->m_contact.type = Bottom;
	}

	return true; 
}

PUBLIC bool checkWallCollisionBall(Ball theBall)
{
	int ballLeft = theBall->m_rec.x;
    int ballRight = theBall->m_rec.x + theBall->m_rec.w;
    int ballTop = theBall->m_rec.y;
    int ballBottom = theBall->m_rec.y + theBall->m_rec.h;


	if (ballLeft < 0.0f)
	{
		theBall->m_contact.type = Left;
	}
	else if (ballRight > WINDOW_WIDTH)
	{
		theBall->m_contact.type = Right;
	}
	else if (ballTop < 0.0f)
	{
		theBall->m_contact.type = Top;
		theBall->m_contact.type = -ballTop;
	}
	else if (ballBottom > WINDOW_HEIGHT)
	{
		theBall->m_contact.type = Bottom;
		theBall->m_contact.type = WINDOW_HEIGHT - ballBottom;
	}
    	return true;
}


PUBLIC void handleCollisionBall(Ball theBall){  
    theBall->m_position->x = theBall->m_position->x + theBall->m_contact.penetration;

	theBall->m_velocity->x = -theBall->m_velocity->x;

		if (theBall->m_contact.type == Top)
		{
			theBall->m_velocity->y = -.75f * 1;
		}
		else if (theBall->m_contact.type == Bottom)
		{
			theBall->m_velocity->y = 0.75f * 1;
		}
}


PUBLIC void ballDraw(Ball theBall, SDL_Renderer* renderer){
    theBall->m_rec.y = (int) (theBall->m_position->y);
    theBall->m_rec.x = (int) (theBall->m_position->x);

	SDL_RenderFillRect(renderer, &theBall->m_rec);
}

