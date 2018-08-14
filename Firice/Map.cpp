#include <iostream>
#include <fstream>
using namespace std;

#include "Map.h"

Map::Map()
{
	Level = 0;
	Size.Width = 0;
	Size.Height = 0;
	mMapData = nullptr; // null pointer
}
Map::~Map()
{
	mMapData = nullptr;
}

bool Map::Initialize(matrix data, ::Size size, int lvl)
{
	if (data == nullptr || size.Height == 0 || size.Width == 0 || lvl <= 0) return false;

	mMapData = data;
	Size.Width = size.Width;
	Size.Height = size.Height;
	Level = lvl;

	return true;
}

matrix Map::ReadFromFile(char* filePath, matrix data)
{
	ifstream inputFile;
	inputFile.open("map.txt", ifstream::in);
	
	if(inputFile)
	{
		char value ;
		while(inputFile >> value)
		{
			cout << value;
		}
		
		inputFile.close();
	}

	return data;
}

