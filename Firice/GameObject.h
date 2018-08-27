#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H
#include "CommonTypes.h"
#include <SDL.h>

class GameObject
{
protected:
	Point2 center;	
public:
	GameObject();
	virtual ~GameObject();

	void setCenter(int x, int y);
	void setCenter(Point2 p);
	Point2 getCenter() const { return center; };
	Size size;
	virtual void draw(SDL_Renderer* renderer, SDL_Texture* texture);
	virtual void update(unsigned long currentTime);
};

#endif