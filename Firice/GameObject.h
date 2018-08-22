#pragma once
#include "CommonTypes.h"
#include <SDL.h>
#include "Game.h"

class GameObject
{
protected:
	Point2 center;
	Game* game;
public:
	GameObject();
	~GameObject();

	void setCenter(int x, int y);
	Point2 getCenter() const { return center; };
	Size size;
	virtual void draw(SDL_Renderer* renderer, SDL_Texture* texture, SDL_RendererFlip flip);
	virtual void update(unsigned long currentTime);
};

