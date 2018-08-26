#ifndef GAME_H
#define GAME_H
#include "CommonTypes.h"
#include <SDL.h>
#include "Mage.h"


class Game
{
private:
	bool isRunning;
	Vector2 charDirection;
	Vector2 currentCharDirection;

	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_Texture* fireTexture;
	SDL_Texture* iceTexture;
	SDL_Surface* fireSurface;
	SDL_Surface* iceSurface;

	class Mage* charFire;
	class Mage* charIce;

public:
	Game();
	~Game();


	bool initialize(const char* title, Point2 position, Size screenSize, int flags);
	void run();

	void processInput();
	void update();
	
	void render();

	bool running() const { return isRunning; }
};

#endif