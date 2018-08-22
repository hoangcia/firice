#ifndef MAGE_H
#define MAGE_H
#include <SDL.h>
#include "GameObject.h"
#include "CommonTypes.h"
enum CHARACTER_STATUS { None = 0, Idle = 1, Walking = 2, Attacking = 4, Jumping = 8, Running = 16 };
class Mage :
	public GameObject
{
private:
	
public:
	Mage();
	Mage(Size s, Point2 c);
	~Mage();

	Point2 currentAnimatedFrame;	
	SDL_Rect getSrcRect();

	unsigned int Status;
	unsigned long LastTime;
	void update(unsigned long currentTime);
	void draw(SDL_Renderer* renderer, SDL_Texture* texture, SDL_RendererFlip flip);
};

#endif