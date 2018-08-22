#pragma once
#include "CommonTypes.h"
#include <SDL.h>

class GameObject
{
protected:
	Point2 center;
public:
	GameObject();
	~GameObject();

	void setCenter(int x, int y);
	Point2 getCenter() { return center; };
	Size size;
	virtual void draw(SDL_Renderer* renderer, SDL_Texture* texture, SDL_RendererFlip flip);
	virtual void update(unsigned long currentTime);
};

