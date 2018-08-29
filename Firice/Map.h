#pragma once
#include "GameObject.h"
#include "Block.h"

class Map :
	public GameObject
{
private:
	class Block* blocks;
public:
	Map();
	Map(Size s, Point2 c);
	~Map();

	void update(unsigned long currentTime) override;
	void draw(SDL_Renderer* renderer, SDL_Texture* texture) override;
};

