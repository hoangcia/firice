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

matrix Map::ReadFromFile(string filePath, matrix& data, uInt rows, uInt cols)
{
	ifstream inputFile;
	inputFile.open(filePath, ifstream::in);
	delete data;

	data = new unsigned short*[rows];	

	if(inputFile)
	{
		unsigned short value;
		for (uInt r = 0; r < rows; ++r) {
			data[r] = new unsigned short[cols];
			for (uInt c = 0; c < cols; ++c) {
				if (inputFile >> value) {
					//*(*data + (r * cols + c)) = value;
					*(data[r] + c) = value;
				}
				else {
					inputFile.close();
					return data;
				}
			}
		}
		inputFile.close();
	}

	return data;
}

bool Map::SetData(matrix data) {
	mMapData = data;
	return true;
}

matrix Map::GetData() {	
	return mMapData;
}