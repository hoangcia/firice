#include "Game.h"
#include <iostream>
#include "Constants.h"
#include <SDL_image.h>
#include "Mage.h"
#include "Map.h"

Game::Game()
{
	window = nullptr;
	renderer = nullptr;
	iceSurface = nullptr;
	fireSurface = nullptr;
	mapSurface = nullptr;

	iceTexture = nullptr;
	fireTexture = nullptr;
	mapTexture = nullptr;

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
	window = SDL_CreateWindow(title, static_cast<int>(position.x), static_cast<int>(position.y), screenSize.width, screenSize.height, flags);
	
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
	mapSurface = IMG_Load(".\\assets\\BG.png");
	mapTexture = SDL_CreateTextureFromSurface(renderer, mapSurface);
	
	fireSurface = IMG_Load(".\\assets\\redmage.png");
	fireTexture = SDL_CreateTextureFromSurface(renderer, fireSurface);

	iceSurface = IMG_Load(".\\assets\\bluemage.png");
	iceTexture = SDL_CreateTextureFromSurface(renderer, iceSurface);	

	charFire = new Mage(Size{ ANIMATED_FRAME_WIDTH, ANIMATED_FRAME_HEIGHT }, Point2{100,500});
	charIce = new Mage(Size{ ANIMATED_FRAME_WIDTH, ANIMATED_FRAME_HEIGHT }, Point2{600,500});

	map = new Map(Size{ DEFAULT_SCREEN_WIDTH,DEFAULT_SCREEN_HEIGHT }, Point2{ DEFAULT_SCREEN_WIDTH / 2, DEFAULT_SCREEN_HEIGHT / 2 });

	charFire->setMap(map);
	charIce->setMap(map);

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
	GameEvent* e = nullptr;
	
	const Uint8* keyStates = nullptr;
	
	ax = 0.0f;
	

	while(SDL_PollEvent(&event))
	{
		SDL_Scancode scancode = (SDL_Scancode)NULL;

		switch (event.type)
		{
			case SDL_QUIT:
				isRunning = false;
				break;
			
			case SDL_KEYUP:
				 scancode = event.key.keysym.scancode;
				switch(scancode)
				{
					case SDL_SCANCODE_SPACE:
						delete e;
						e = new GameEvent;

						jumpingVelocity = CHAR_JUMPING_VELOCITY;
						e->Type = CharacterJump;
						e->Parameters.insert(std::make_pair("jumpingVelocity", jumpingVelocity));
						gameEvents.push(*e);
					break;

					case SDL_SCANCODE_D:
					case SDL_SCANCODE_RIGHT: 
					case SDL_SCANCODE_A:
					case SDL_SCANCODE_LEFT:
						delete e;
						e = new GameEvent;
						e->Type = CharacterStopMoving;					
						ax = -CHAR_MOVING_ACCELERATION;
						e->Parameters.insert(std::make_pair("ax", ax));
						e->Parameters.insert(std::make_pair("direction",  scancode == SDL_SCANCODE_A || scancode == SDL_SCANCODE_LEFT? Left : Right));
						gameEvents.push(*e);

						break;
					default: break;
				}
				break;
			case SDL_KEYDOWN:
				scancode = event.key.keysym.scancode;
				switch (scancode)
				{					
					case SDL_SCANCODE_D:
					case SDL_SCANCODE_RIGHT:
					case SDL_SCANCODE_A:
					case SDL_SCANCODE_LEFT:
						delete e;
						e = new GameEvent;
						e->Type = CharacterMove;
						ax = CHAR_MOVING_ACCELERATION;
						e->Parameters.insert(std::make_pair("ax", ax));
						e->Parameters.insert(std::make_pair("direction", scancode == SDL_SCANCODE_A || scancode == SDL_SCANCODE_LEFT ? Left : Right));
						gameEvents.push(*e);					
						break;
					default: break;
				}
				break;
			default: break;
		}				
	}

	keyStates = SDL_GetKeyboardState(nullptr);

	if (keyStates[SDL_SCANCODE_ESCAPE])
	{
		isRunning = false;
	}

	if (keyStates[SDL_SCANCODE_A] || keyStates[SDL_SCANCODE_LEFT])
	{
		delete e;
		e = new GameEvent;
		e->Type = CharacterMove;
		ax = CHAR_MOVING_ACCELERATION;
		e->Parameters.insert(std::make_pair("ax", ax));
		e->Parameters.insert(std::make_pair("direction", CHAR_DIRECTION_X::Left));
		gameEvents.push(*e);
	}
	else if (keyStates[SDL_SCANCODE_D] || keyStates[SDL_SCANCODE_RIGHT])
	{
		delete e;
		e = new GameEvent;
		e->Type = CharacterMove;
		ax = CHAR_MOVING_ACCELERATION;
		e->Parameters.insert(std::make_pair("ax", ax));
		e->Parameters.insert(std::make_pair("direction", CHAR_DIRECTION_X::Right));
		gameEvents.push(*e);
	}
	delete e;
	e = nullptr;
}
void Game::update()
{			
	charFire->update(SDL_GetTicks(), gameEvents, false);
	charIce->update(SDL_GetTicks(), gameEvents, true);
	//clear gameEvents for next loop
	while(!gameEvents.empty())
	{
		gameEvents.pop();
	}
}
void Game::render()
{
	SDL_RenderClear(renderer);

	SDL_SetRenderDrawColor(renderer, 34, 128, 200, SDL_ALPHA_OPAQUE);

	map->draw(renderer, mapTexture);

	charFire->draw(renderer, fireTexture);
	charIce->draw(renderer, iceTexture);
	

	SDL_RenderPresent(renderer);
}

