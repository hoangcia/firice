#include <SDL.h>
#include "Game.h"
#include "Constants.h"

const char* GAME_TITLE = "Firice";

int main(int arg, char** args)
{
	Game* game = nullptr;
	Size* size = nullptr;	
	Point2 position = { SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED };
	game = new Game();
	size = new Size();

	size->width = DEFAULT_SCREEN_WIDTH;
	size->height = DEFAULT_SCREEN_HEIGHT;
	
	if(game->initialize(GAME_TITLE, position, *size, 0))
	{
		game->run();
	}

	delete size;
	delete game;

	return 0;
}
