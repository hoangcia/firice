#include <SDL.h>
#include <SDL_image.h>

#include "Game.h"

int main(int arg, char** args) {
	Game game;
	bool success = game.Initialize();
	if (success) {
		game.Run();
	}
	game.Shutdown();
	return 0;
}