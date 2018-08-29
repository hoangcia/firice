#include "Map.h"



Map::Map()
{
	blocks = nullptr;
}

Map::Map(Size s, Point2 c)
{
	center = c;
	size = s;
}

Map::~Map()
{
}
void Map::update(unsigned long currentTime)
{
	
}
void Map::draw(SDL_Renderer* renderer, SDL_Texture* texture)
{
	SDL_Rect srcRect = { 0, 0, size.width, size.height };
	SDL_Rect dstRect = { center.x - (size.width / 2.0f), center.y - (size.height / 2.0f), size.width, size.height };

	SDL_RenderCopy(renderer, texture, &srcRect, &dstRect);
}
