#ifndef MAGE_H
#define MAGE_H
#include <SDL.h>
#include <queue>
#include "GameObject.h"
#include "CommonTypes.h"
#include "GameEvent.h"
#include "Map.h"

enum CHARACTER_STATUS { None = 0, Idle = 1, Walking = 2, Attacking = 4, Jumping = 8, Running = 16, Falling = 32 };

enum CHAR_DIRECTION_X {NoneX= 0, Left = -1, Right = 1};
enum CHAR_DIRECTION_Y {NoneY = 0, Up = -1, Down = 1 };

class Mage :
	public GameObject
{
	
private:
	class Map* map;
public:
	Mage();
	Mage(Size s, Point2 c);
	~Mage();
	
	Vector2 currentAnimatedFrame;		

	unsigned int Status;
	unsigned long LastTime;
	float VelocityX;
	float Acceleration;
	float VelocityY;
	CHAR_DIRECTION_X DirectionX;
	CHAR_DIRECTION_Y DirectionY;

	void setMap(Map* m);
	
	void update(unsigned long currentTime) override;
	void update(unsigned long currentTime, std::queue<GameEvent> events, bool revertMoving);

	void draw(SDL_Renderer* renderer, SDL_Texture* texture) override;
};

#endif