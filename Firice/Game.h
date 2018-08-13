#pragma once
#include <SDL.h>
#include <SDL_image.h>

#include "CommonTypes.h"

class Game {
private:
	uInt mScores;
	uInt mTime;
	void Update();
	void ProcessInput();
	void GenerateOutput();

	SDL_Window* mWindow;
	SDL_Renderer* mRenderer;

	SDL_Surface* mSpriteFire;
	SDL_Texture* mFireTexture;
	
	SDL_Surface* mBackground;
	SDL_Texture* mBackgroundTexture;


	SDL_Surface* mBlock;
	SDL_Texture* mBlockTexture;
	
	unsigned short mFrame = 0;	

	Uint32 mTicksCount;
	float mFrameTicksCount;

	Vector2 mDirection;
	Vector2 mCurrentDirection;

	bool mIsRunning;	
	Vector2 mFirePos;
	

	const uInt SCREEN_WIDTH = 1024;
	const uInt SCREEN_HEIGHT = 768;
	const uInt LIMIT_FPS = 60;
	const uInt SPRITE_FRAME_LIMIT_FPS = 30;
	const uInt SPRITE_FRAME_LIMIT = 16;
	const float DEFAUT_CHARACTER_VELOCITY = 300.0f;
	const uInt FRAME_WIDTH = 60;
	const uInt FRAME_HEIGHT = 60;
public:
	Game();
	~Game();
	//Initialize the game
	bool Initialize();
	bool Start();
	bool Stop();
	bool Run();
	bool Pause();
	bool Resume();
	//Shutdown the game
	void Shutdown();			
};