#pragma once
#include "GameObject.h"

enum BLOCK_TYPE{Soil, Tree, Water, Bush};
class Block :
	public GameObject
{
public:
	Block();
	~Block();
};

