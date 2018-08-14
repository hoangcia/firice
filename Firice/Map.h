#pragma once
#include "Block.h"

class Map {
private:
	matrix mMapData;
	
public:
	Map();
	~Map();
	bool Initialize(matrix data, Size size, int lvl);
	unsigned short Level;	
	Size Size;

	static matrix ReadFromFile(char* filePath, matrix data);
};