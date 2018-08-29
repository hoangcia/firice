#pragma once
#include "GameObject.h"
class Map :
	public GameObject
{
public:
	Map();
	Map(Size s, Point2 c);
	~Map();

	void update(unsigned long currentTime) override;
	void draw(SDL_Renderer* renderer, SDL_Texture* texture) override;
};
