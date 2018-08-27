#ifndef MAGE_H
#define MAGE_H
#include <SDL.h>
#include "GameObject.h"
#include "CommonTypes.h"
#include "GameEvent.h"
#include <queue>

enum CHARACTER_STATUS { None = 0, Idle = 1, Walking = 2, Attacking = 4, Jumping = 8, Running = 16 };

enum CHAR_DIRECTION{Left = -1, Right = 1};

class Mage :
	public GameObject
{
	
public:
	Mage();
	Mage(Size s, Point2 c);
	~Mage();

	Point2 currentAnimatedFrame;		

	unsigned int Status;
	unsigned long LastTime;
	float VelocityX;
	float Acceleration;
	float VelocityY;
	CHAR_DIRECTION Direction;

	void update(unsigned long currentTime) override;
	void update(unsigned long currentTime, std::queue<GameEvent> events, bool revertMoving);

	void draw(SDL_Renderer* renderer, SDL_Texture* texture) override;
};

#endif