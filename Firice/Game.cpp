#include "Game.h"
#include <iostream>
#include "Constants.h"

Game::Game()
{
	window = nullptr;
	renderer = nullptr;
	iceSurface = nullptr;
	fireSurface = nullptr;
	iceTexture = nullptr;
	fireTexture = nullptr;
	charFire = nullptr;
	charIce = nullptr;
}


Game::~Game()
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}
bool Game::initialize(const char* title, Point2 position, Size screenSize, int flags)
{
	int initError = SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
	if(initError){
		SDL_Log("Failed to init SDL: %s", SDL_GetError());
		return false;
	}
	window = SDL_CreateWindow(title, position.x, position.y, screenSize.width, screenSize.height, flags);
	
	if(!window)
	{
		SDL_Log("Failed to create SDL Window: %s ", SDL_GetError());
		return false;
	}
	renderer = SDL_CreateRenderer(window, -1, flags);
	if(!renderer)
	{
		SDL_Log("Failed to create SDL Renderer: %s ", SDL_GetError());
		return false;
	}

	//load media
	fireSurface = IMG_Load(".\\assets\\redmage.png");
	fireTexture = SDL_CreateTextureFromSurface(renderer, fireSurface);

	iceSurface = IMG_Load(".\\assets\\bluemage.png");
	iceTexture = SDL_CreateTextureFromSurface(renderer, iceSurface);

	charFire = new Mage(Size{ ANIMATED_FRAME_WIDTH, ANIMATED_FRAME_HEIGHT }, Point2{100,100});
	charIce = new Mage(Size{ ANIMATED_FRAME_WIDTH, ANIMATED_FRAME_HEIGHT }, Point2{300,300});
	

	isRunning = true;

	return true;
}
void Game::run()
{
	Uint32 startTime = 0;	
	Uint32 count = 0;
	Uint32 frameTime = 0;

	while(running())
	{
		startTime = SDL_GetTicks();
		processInput();
		update();
		render();

		frameTime = SDL_GetTicks() - startTime;

		if(frameTime < SECONDS_PER_FRAME)
		{
			SDL_Delay(SECONDS_PER_FRAME - frameTime);			
		}

	}
}
void Game::processInput()
{
	SDL_Event event;
	const Uint8* keyStates = nullptr;

	while(SDL_PollEvent(&event))
	{
		switch(event.type)
		{
			case SDL_QUIT: 
				isRunning = false; 
				break;
			case SDL_KEYDOWN:
				keyStates = SDL_GetKeyboardState(nullptr);
				if (keyStates[SDL_SCANCODE_ESCAPE])
				{
					isRunning = false;
				}
				break;
			default: break;
		}
		
	}
}
void Game::update()
{
	charFire->update(SDL_GetTicks());
	charIce->update(SDL_GetTicks());
}
void Game::render()
{
	SDL_RenderClear(renderer);

	SDL_SetRenderDrawColor(renderer, 34, 128, 200, SDL_ALPHA_OPAQUE);

	charFire->draw(renderer, fireTexture, SDL_FLIP_NONE);
	charIce->draw(renderer, iceTexture, SDL_FLIP_NONE);

	SDL_RenderPresent(renderer);
}

