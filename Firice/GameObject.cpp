#include "GameObject.h"
#include <SDL.h>


GameObject::GameObject()
{
}


GameObject::~GameObject()
{
}

void GameObject::setCenter(float x, float y)
{
	center.x = x;
	center.y = y;
}

void GameObject::setCenter(Point2 p)
{
	center = p;
}

void GameObject::draw(SDL_Renderer * renderer, SDL_Texture * texture)
{
}
void GameObject::update(unsigned long currentTime)
{
	
}
