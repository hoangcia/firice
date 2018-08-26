#include "GameObject.h"
#include <SDL.h>


GameObject::GameObject()
{
}


GameObject::~GameObject()
{
}

void GameObject::setCenter(int x, int y)
{
	center.x = x;
	center.y = y;
}

void GameObject::setCenter(Point2 p)
{
	center = p;
}

void GameObject::draw(SDL_Renderer * renderer, SDL_Texture * texture, SDL_RendererFlip flip)
{
}
void GameObject::update(unsigned long currentTime)
{
	
}
