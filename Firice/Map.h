#pragma once
#include "Block.h"

class Map {
private:
	shortMatrix mMapData;
	
public:
	bool SetMapData(shortMatrix data);
	unsigned short Width;
	unsigned short Height;

};