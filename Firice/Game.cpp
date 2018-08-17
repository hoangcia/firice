#include <SDL.h>
#include <SDL_image.h>
#include <string>

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
	//load game background
	mBackground = IMG_Load(".\\assets\\BG\\BG.png");
	mBackgroundTexture = SDL_CreateTextureFromSurface(mRenderer, mBackground);

	//load game block	
	for (ushort idx = 1; idx <= 18; ++idx) {
		string path = ".\\assets\\Tiles\\";
		path.append(std::to_string(idx));
		path.append(".png");
		mBlock[idx-1] = IMG_Load(path.c_str());
		
		mBlockTexture[idx - 1] = SDL_CreateTextureFromSurface(mRenderer, mBlock[idx - 1]);
	}
		
	//load game sprite
	mSpriteFire = IMG_Load(".\\assets\\sprite_fire.png");
	mFireTexture = SDL_CreateTextureFromSurface(mRenderer, mSpriteFire);

	mSpriteIce = IMG_Load(".\\assets\\sprite_fire.png");
	mIceTexture = SDL_CreateTextureFromSurface(mRenderer, mSpriteIce);

	//load map
	
		
	std::string path = PREFIX_MAP_NAME;
	path.append(".txt");

	mMap.Size.Width = DEFAULT_MAP_WIDTH;
	mMap.Size.Height = DEFAULT_MAP_HEIGHT;

	matrix data = nullptr;

	Map::ReadFromFile(path, data, mMap.Size.Height, mMap.Size.Width);
	mMap.SetData(data);

	for (int r = 0; r < mMap.Size.Height; ++r) {
		for (int c = 0; c < mMap.Size.Width; ++c) {
			if (data[r][c] == static_cast<unsigned short>(BLOCK_TYPE::CFire)) {
				mFirePos = { static_cast<int>(FRAME_WIDTH) * c + static_cast<int>(FRAME_WIDTH / 2), static_cast<int>(FRAME_HEIGHT) * r + static_cast<int>(FRAME_HEIGHT / 2) };
			}
			if (data[r][c] == static_cast<unsigned short>(BLOCK_TYPE::CIce)) {
				mIcePos = { static_cast<int>(FRAME_WIDTH) * c + static_cast<int>(FRAME_WIDTH / 2), static_cast<int>(FRAME_HEIGHT) * r + static_cast<int>(FRAME_HEIGHT / 2) };
			}
			printf("%d ", data[r][c]);
		}
		printf("\n");
	}

	mFrame = 0;

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
		//mIcePos

		mIcePos.X -= mDirection.X * DEFAUT_CHARACTER_VELOCITY * deltaTime;
		mIcePos.Y += mDirection.Y * DEFAUT_CHARACTER_VELOCITY * deltaTime;

		if (mIcePos.X < (FRAME_WIDTH / 2.0f)) {
			mIcePos.X = FRAME_WIDTH / 2.0f;
		}
		else if (mIcePos.X >(SCREEN_WIDTH - FRAME_WIDTH / 2.0f)) {
			mIcePos.X = (SCREEN_WIDTH - FRAME_WIDTH / 2.0f);
		}

		if (mIcePos.Y < (FRAME_HEIGHT / 2.0f)) {
			mIcePos.Y = FRAME_HEIGHT / 2.0f;
		}
		else if (mIcePos.Y >(SCREEN_HEIGHT - FRAME_HEIGHT / 2.0f)) {
			mIcePos.Y = (SCREEN_HEIGHT - FRAME_HEIGHT / 2.0f);
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
			
			default: break;
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

		if (state[SDL_SCANCODE_LEFT] || state[SDL_SCANCODE_A]) {
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

	SDL_RenderClear(mRenderer);		
		
	//draw background
	SDL_Rect srcBgRect = { 0,0, BG_WIDTH, BG_HEIGHT };
	SDL_Rect dstBgRect = { 0,0, BG_WIDTH, BG_HEIGHT };

	SDL_RenderCopy(mRenderer, mBackgroundTexture, &srcBgRect, &dstBgRect);

	//draw map
	
	SDL_Rect srcBlockRect = { 0, 0, DEFAULT_SPRITE_FRAME_WIDTH, DEFAULT_SPRITE_FRAME_HEIGHT };
	SDL_Rect dstBlockRect = { 0, 0, FRAME_WIDTH, FRAME_HEIGHT };
	SDL_Rect dstBlockRectRender = { 0, 0, FRAME_WIDTH, FRAME_HEIGHT };

	matrix data = mMap.GetData();

	for (int r = 0; r < mMap.Size.Height; ++r) {
		dstBlockRectRender.y = r * FRAME_HEIGHT;
		for (int c = 0; c < mMap.Size.Width; ++c) {
			//mBlockTexture = SDL_CreateTextureFromSurface(mRenderer, mBlock);
			dstBlockRectRender.x = c * FRAME_WIDTH;
			short imgIdx = data[r][c];
			short prev = data[r][c ? c - 1 : c];

			switch (imgIdx){
			case Water_17:
			case Water_18:
					SDL_BlitScaled(mBlock[imgIdx - 1], &srcBlockRect, mBlock[imgIdx - 1], &dstBlockRect);				
					dstBlockRectRender.x -= FRAME_WIDTH;
					SDL_RenderCopy(mRenderer, mBlockTexture[imgIdx - 1], &srcBlockRect, &dstBlockRectRender);				 
					SDL_RenderCopy(mRenderer, mBlockTexture[prev - 1], &srcBlockRect, &dstBlockRectRender);

					dstBlockRectRender.x += FRAME_WIDTH;
					SDL_RenderCopy(mRenderer, mBlockTexture[imgIdx - 1], &srcBlockRect, &dstBlockRectRender);

					dstBlockRectRender.x += FRAME_WIDTH;
					SDL_RenderCopy(mRenderer, mBlockTexture[imgIdx - 1], &srcBlockRect, &dstBlockRectRender);

					dstBlockRectRender.x -= FRAME_WIDTH;
					break;
			case CFire: 

			case CIce: break;
			default:
					SDL_RenderCopy(mRenderer, mBlockTexture[imgIdx - 1], &srcBlockRect, &dstBlockRectRender);
					break;				
			}			
		}
	}	

	//draw fire character
	SDL_RendererFlip fỉeFlipType = mCurrentDirection.X < 0 ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;	

	Vector2 topLeftFire = { (mFrame % 4) * FRAME_WIDTH, (mFrame / 4) * FRAME_HEIGHT };		

	SDL_Rect srcrectFire = { topLeftFire.X, topLeftFire.Y, FRAME_WIDTH, FRAME_HEIGHT };
	SDL_Rect dstrectFire = { mFirePos.X - FRAME_WIDTH/2.0f, mFirePos.Y - FRAME_HEIGHT/2.0f, FRAME_WIDTH, FRAME_HEIGHT };
	
	SDL_RenderCopyEx(mRenderer, mFireTexture, &srcrectFire, &dstrectFire, 0, NULL, fỉeFlipType);

	//draw fire character
	SDL_RendererFlip iceFlipType = mCurrentDirection.X < 0 ?  SDL_FLIP_NONE : SDL_FLIP_HORIZONTAL;

	Vector2 topLeftIce = { (mFrame % 4) * FRAME_WIDTH, (mFrame / 4) * FRAME_HEIGHT };

	SDL_Rect srcrectIce= { topLeftIce.X, topLeftIce.Y, FRAME_WIDTH, FRAME_HEIGHT };
	SDL_Rect dstrectIce = { mIcePos.X - FRAME_WIDTH / 2.0f, mIcePos.Y - FRAME_HEIGHT / 2.0f, FRAME_WIDTH, FRAME_HEIGHT };

	SDL_RenderCopyEx(mRenderer, mFireTexture, &srcrectIce, &dstrectIce, 0, NULL, iceFlipType);
	//bring to front buffer
	SDL_RenderPresent(mRenderer);
}

void Game::Shutdown() {
	SDL_DestroyRenderer(mRenderer);
	SDL_DestroyWindow(mWindow);
	SDL_Quit();
}

