#pragma once
#include "CommonTypes.h"

enum BLOCK_TYPE {None, Character, Brick, Water, Lava};

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

