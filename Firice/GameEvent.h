#pragma once
#include <map>

enum GAME_EVENT_TYPE { Nothing, CharacterMove, CharacterStopMoving, CharacterJump };

class GameEvent
{
public:
	GAME_EVENT_TYPE Type;
	std::map<std::string, float> Parameters;

	GameEvent();
	~GameEvent();
};

