#ifndef GAME_H
#define GAME_H
#include "CommonTypes.h"
#include <SDL.h>
#include <SDL_image.h>
#include "Mage.h"

class Game
{
private:
	bool isRunning;
	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_Texture* fireTexture;
	SDL_Texture* iceTexture;
	SDL_Surface* fireSurface;
	SDL_Surface* iceSurface;
	Mage* charFire;
	Mage* charIce;

public:
	Game();
	~Game();


	bool initialize(const char* title, Point2 position, Size screenSize, int flags);
	void run();

	void processInput();
	void update();
	
	void render();

	bool running() { return isRunning; }
};

#endif