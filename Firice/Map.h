#pragma once
#include <string>
#include "Block.h"
using namespace std;

class Map {
private:	
	matrix mMapData;
public:
	
	Map();
	~Map();
	bool Initialize(matrix data, Size size, int lvl);
	unsigned short Level;	
	Size Size;

	static matrix ReadFromFile(string filePath, matrix& data, uInt rows, uInt cols);
	bool SetData(matrix data);
	matrix GetData();
};