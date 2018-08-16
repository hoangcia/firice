#pragma once
#include "CommonTypes.h"

enum BLOCK_TYPE {
	None = 0,
	Soil_1,
	Soil_2,
	Soil_3,
	Soil_4,
	Soil_5,
	Soil_6,
	Soil_7,
	Soil_8,
	Soil_9,
	Soil_10,
	Soil_11,
	Soil_12,
	Soil_13,
	Soil_14,
	Soil_15,
	Soil_16,
	Water_17,
	Water_18,
	CFire, //Character Fire
	CIce //Character Ice
};

class Block {
	private:
		BLOCK_TYPE _blockType;
		Vector2 _position;
		Vector2 _originPosition;
		Vector2 _basePosition;

		uInt _width;
		uInt _height;		

	protected:

	public:
		uInt GetWidth();
		uInt GetHeight();
		Vector2 GetPosition();
		Vector2 GetBasePosition();
		Vector2 GetAbsPosition();

		void SetOriginPosition();
		void SetPosition();
		void SetWidth();
		void SetHeight();

		bool IsCollision(Block block);
};

