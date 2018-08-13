#include <SDL.h>
#include <SDL_image.h>

#include "CommonTypes.h"
#include "Game.h"

Game::Game() {}
Game::~Game() {}
bool Game::Initialize() {
	mIsRunning = true;
	int sdlResult = SDL_Init(SDL_INIT_VIDEO);
	if (sdlResult != 0) {
		SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
		return false;
	}

	mWindow = SDL_CreateWindow("Firice",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		SCREEN_WIDTH,
		SCREEN_HEIGHT,
		SDL_WINDOW_SHOWN
	);

	if (!mWindow) {
		SDL_Log("Failed to create window: %s", SDL_GetError());
		return false;
	}

	//create renderer
	mRenderer = SDL_CreateRenderer(
	mWindow,
		-1,
		SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
	);
	if (!mRenderer) {
		SDL_Log("Failed to create renderer: %s", SDL_GetError());
		return false;
	}
	//load game sprite
	mSpriteFire = IMG_Load("sprite_fire.png");
	mTexture = SDL_CreateTextureFromSurface(mRenderer, mSpriteFire);	

	mFrame = 0;

	mFirePos = { 300,300 };
	return true;
}
bool Game::Run() { 
	while (mIsRunning) {
		ProcessInput();
		Update();
		GenerateOutput();
	}
	return true; 
}
void Game::Update() {
		
	while (!SDL_TICKS_PASSED(SDL_GetTicks(), mTicksCount + (1000 / LIMIT_FPS)));
	
	float deltaTime = (SDL_GetTicks() - mTicksCount) / 1000.0f;	
	//clamp maximum delta time value
	if (deltaTime > 0.05f) {
		deltaTime = 0.05f;
	}	

	mTicksCount = SDL_GetTicks();
	
	if (mFrameTicksCount + deltaTime < (1.0f/SPRITE_FRAME_LIMIT_FPS)) {		
		mFrameTicksCount += deltaTime;
	}
	else {
		mFrameTicksCount = 0;
		mFrame = (mFrame + 1) % SPRITE_FRAME_LIMIT;
	}

	// TODO: Update objects in game world as function
		
	if (mDirection.X != 0 || mDirection.Y != 0) {
				
		//mFirePos

		mFirePos.X += mDirection.X * DEFAUT_CHARACTER_VELOCITY * deltaTime;
		mFirePos.Y += mDirection.Y * DEFAUT_CHARACTER_VELOCITY * deltaTime;

		if (mFirePos.X < (FRAME_WIDTH / 2.0f)) {
			mFirePos.X = FRAME_WIDTH / 2.0f;
		}
		else if (mFirePos.X > (SCREEN_WIDTH - FRAME_WIDTH / 2.0f)) {
			mFirePos.X = (SCREEN_WIDTH - FRAME_WIDTH / 2.0f);
		}

		if (mFirePos.Y < (FRAME_HEIGHT / 2.0f)) {
			mFirePos.Y = FRAME_HEIGHT / 2.0f;
		}
		else if (mFirePos.Y >(SCREEN_HEIGHT - FRAME_HEIGHT / 2.0f)) {
			mFirePos.Y = (SCREEN_HEIGHT - FRAME_HEIGHT / 2.0f);
		}
	}
}
void Game::ProcessInput() {
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		switch (event.type) {
			case SDL_QUIT: 
				mIsRunning = false;
				break;			
		}

		//Get state of keyboard
		
		mDirection = { 0,0 };

		const Uint8* state = SDL_GetKeyboardState(NULL);
		if (state[SDL_SCANCODE_ESCAPE]) {
			mIsRunning = false;
		}
		else if (state[SDL_SCANCODE_UP] || state[SDL_SCANCODE_W]) {
			mDirection.Y = -1;			
		}
		else if (state[SDL_SCANCODE_DOWN] || state[SDL_SCANCODE_S]) {			
			mDirection.Y = 1;			
		}						
		else if (state[SDL_SCANCODE_LEFT] || state[SDL_SCANCODE_A]) {
			mDirection.X = -1;
			mCurrentDirection.X = mDirection.X;
		}
		else if (state[SDL_SCANCODE_RIGHT] || state[SDL_SCANCODE_D]) {
			mDirection.X = 1;
			mCurrentDirection.X = mDirection.X;
		}
	}
}
void Game::GenerateOutput() {
	
	SDL_SetRenderDrawColor(
		mRenderer,
		66,  // R
		138,  // G
		244,// B
		255 // A
	);
	SDL_RenderClear(mRenderer);		
	
	SDL_RendererFlip flipType = mCurrentDirection.X < 0 ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;

	SDL_SetRenderDrawColor(mRenderer, 201, 67, 6, 255);

	Vector2 topLeft = { (mFrame % 4) * FRAME_WIDTH, (mFrame / 4) * FRAME_HEIGHT };		

	SDL_Rect srcrect = { topLeft.X, topLeft.Y, FRAME_WIDTH, FRAME_HEIGHT };
	SDL_Rect dstrect = { mFirePos.X - FRAME_WIDTH/2.0f, mFirePos.Y - FRAME_HEIGHT/2.0f, FRAME_WIDTH, FRAME_HEIGHT };
	
	SDL_RenderCopyEx(mRenderer, mTexture, &srcrect, &dstrect, 0, NULL, flipType);
	SDL_RenderPresent(mRenderer);
}

void Game::Shutdown() {
	SDL_DestroyRenderer(mRenderer);
	SDL_DestroyWindow(mWindow);
	SDL_Quit();
}
