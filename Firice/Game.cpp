#include "Game.h"
#include <iostream>
#include "Constants.h"
#include <SDL_image.h>
#include "Mage.h"

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

	//initialize game objects
	charFire->LastTime = SDL_GetTicks();
	charIce->LastTime = SDL_GetTicks();

	isRunning = true;

	return true;
}
void Game::run()
{
	Uint32 startTime = 0;	
	Uint32 count = 0;
	Uint32 frameTime = 0;
	currentCharDirection = { 1,0 };

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
	
	ax = 0.0f;
	
	while(SDL_PollEvent(&event))
	{
		switch (event.type)
		{
			case SDL_QUIT:
				isRunning = false;
				break;
			
			case SDL_KEYUP:
				switch(event.key.keysym.scancode)
				{
					case SDL_SCANCODE_SPACE: break;

					case SDL_SCANCODE_D:
					case SDL_SCANCODE_RIGHT: 
					case SDL_SCANCODE_A:
					case SDL_SCANCODE_LEFT: 
						ax = -CHAR_ACCELERATION;  
						break;
					default: break;
				}
				break;
			case SDL_KEYDOWN:
				switch (event.key.keysym.scancode)
				{
				case SDL_SCANCODE_SPACE: break;

				case SDL_SCANCODE_D:
				case SDL_SCANCODE_RIGHT:
				case SDL_SCANCODE_A:
				case SDL_SCANCODE_LEFT:
					ax = CHAR_ACCELERATION;
					break;
				default: break;
				}
				break;
			default: break;
		}

		charDirection = { 0,0 };
		keyStates = SDL_GetKeyboardState(nullptr);

		if (keyStates[SDL_SCANCODE_ESCAPE])
		{
			isRunning = false;
		}

		if (keyStates[SDL_SCANCODE_A] || keyStates[SDL_SCANCODE_LEFT])
		{
			charDirection.x = -1;
			currentCharDirection.x = -1;			
		}
		else if (keyStates[SDL_SCANCODE_D] || keyStates[SDL_SCANCODE_RIGHT])
		{
			charDirection.x = 1;
			currentCharDirection.x = 1;			
		}
		/*
		if (keyStates[SDL_SCANCODE_W] || keyStates[SDL_SCANCODE_UP])
		{
			charDirection.y = -1;
			currentCharDirection.y = -1;
		}
		else if (keyStates[SDL_SCANCODE_S] || keyStates[SDL_SCANCODE_DOWN])
		{
			charDirection.y = 1;
			currentCharDirection.y = 1;
		}
		*/
	}
}
void Game::update()
{
	Vector2 revertedDirectionX = { -1 * charDirection.x, charDirection.y };

	if (charDirection.x != 0 || charDirection.y != 0) {
		charFire->Status = CHARACTER_STATUS::Running; 
		charIce->Status = CHARACTER_STATUS::Running;

	}

	charFire->update(SDL_GetTicks(), charDirection, ax);
	charIce->update(SDL_GetTicks(), revertedDirectionX, ax);

}
void Game::render()
{
	SDL_RenderClear(renderer);

	SDL_SetRenderDrawColor(renderer, 34, 128, 200, SDL_ALPHA_OPAQUE);
	
	SDL_RendererFlip flip = currentCharDirection.x < 0 ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;

	charFire->draw(renderer, fireTexture, flip);
	charIce->draw(renderer, iceTexture, flip == SDL_FLIP_NONE ? SDL_FLIP_HORIZONTAL: SDL_FLIP_NONE);

	SDL_RenderPresent(renderer);
}

