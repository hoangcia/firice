#include "Mage.h"
#include "Constants.h"

Mage::Mage()
{
	currentAnimatedFrame = Point2{ 0,0 };
	LastTime = 0;
	Status = CHARACTER_STATUS::Idle;
	VelocityX = 0.0f;
	VelocityY = 0.0f;
	Acceleration = 0.0f;
}
Mage::Mage(Size s, Point2 c):Mage()
{
	size = s;	
	center = c;	
}

Mage::~Mage()
{
}
void Mage::update(unsigned long currentTime) {
	
	if ((currentTime - LastTime) > (1000 / (LIMIT_ANIMATED_FPS * (1 + static_cast<int>(log2(Status)))))) {
		if ((Status & Running) == Running || (Status & Idle) == Idle) {
			currentAnimatedFrame.x = (currentAnimatedFrame.x + 1) % 4;
			currentAnimatedFrame.y = (static_cast<int>(log2(Status)));
		}
		
		if((Status & Jumping) == Jumping || (Status & Falling) == Falling){
				currentAnimatedFrame.x = 1;
				currentAnimatedFrame.y = (static_cast<int>(log2((int)Jumping)));				
		}
		
		LastTime = currentTime;
	}
}
void Mage::update(unsigned long currentTime, std::queue<GameEvent> events, bool revertMoving)
{
	float deltaTime = (currentTime - LastTime) / 1000.0f;
	float ax = 0.0f;
	bool isGameEventsEmpty = events.empty();

	if(deltaTime > 0.05f)
	{
		deltaTime = 0.05f;
	}
	
	while(!events.empty())
	{
		GameEvent event = events.front();
		switch(event.Type)
		{
			case GAME_EVENT_TYPE::Nothing: break;

			case GAME_EVENT_TYPE::CharacterStopMoving:
			case GAME_EVENT_TYPE::CharacterMove:
				if((Status & Idle) == Idle) Status = Status ^ Idle;
				Status = Status | Running;
				ax = event.Parameters["ax"];
				DirectionX = static_cast<CHAR_DIRECTION_X>(static_cast<int>(event.Parameters["direction"]));				

				Acceleration = ax;
			
				break;			
				
			case GAME_EVENT_TYPE::CharacterJump:
				if ((Status & Jumping) != Jumping && (Status & Falling) != Falling)
				{
					Status = Status | Jumping;
					VelocityY = event.Parameters["jumpingVelocity"];
				}
				break;

			default: break;
		}
		events.pop();
	}

	/*Update movement velocity*/
	
	if (revertMoving && !isGameEventsEmpty) DirectionX = static_cast<CHAR_DIRECTION_X>(-1 * DirectionX);	

	VelocityX += Acceleration;

	if (VelocityX < 0.0f) {
		VelocityX = 0.0f;
		Acceleration = 0.0f;
		if((Status & Running) == Running)Status = Status ^ Running;
		Status = Status | Idle;
	}
	else if (VelocityX > CHAR_MAX_VELOCITY)
	{
		Status = Status | Running;
		VelocityX = CHAR_MAX_VELOCITY;
	}
	/*Update jumping velocity*/
	DirectionY = ((Status & Jumping) == Jumping ? Up : (Status & Falling) == Falling ? Down : NoneY);

	if ((Status & Jumping) == Jumping)
	{
		VelocityY -= (GAME_GRAVITY);
	}
	else if ((Status & Falling )== Falling) {
		VelocityY += (GAME_GRAVITY);
	}

	if((Status & Jumping) == Jumping && VelocityY <= 0)
	{
		Status = Status ^ Jumping;
		Status = Status | Falling;
	}
	/*Set new position*/
	Point2 const newPos = { center.x + deltaTime * VelocityX * DirectionX , center.y + deltaTime*VelocityY * DirectionY};
	//check round border
	if (newPos.x >= (size.width / 2) &&		
		newPos.x + size.width / 2 <= DEFAULT_SCREEN_WIDTH		
		)
	{		

		//detect collision

		//set positions
		setCenter(newPos.x, center.y);
	}
	else
	{
		Acceleration = 0.0f;
		VelocityX = 0.0f;
		if((newPos.x + (size.width / 2)) > DEFAULT_SCREEN_WIDTH)
		{
			setCenter(DEFAULT_SCREEN_WIDTH - (size.width / 2), center.y);
		}
		else
		{
			setCenter(size.width / 2, center.y);
		}
		if((Status & Running) == Running) Status = Status ^ Running;

		Status = Status | Idle;
	}

	if(newPos.y >= (size.height / 2) && 
		newPos.y + size.height / 2 <= DEFAULT_SCREEN_HEIGHT)
	
	{
		//detect collision

		//set positions
		setCenter(center.x, newPos.y);
	}
	else
	{		
		VelocityY = 0.0f;
		
		if (newPos.y < (size.height / 2))
		{
			if(Status & Jumping) Status = Status ^ Jumping;
			Status = Status | Falling;
			setCenter(center.x, size.height / 2);
		}
		else {
			setCenter(center.x, DEFAULT_SCREEN_HEIGHT - size.height / 2);

			if((Status & Falling) == Falling) Status = Status ^ Falling;
			/*
			if (isGameEventsEmpty && (Status & Running) == Running) {
					Status = Status ^ Running;
					Status = Status | Idle;				
			}
			*/
		}
	}
	
	update(currentTime);
}
void Mage::draw(SDL_Renderer* renderer, SDL_Texture* texture) {
	SDL_Rect srcRect = { currentAnimatedFrame.x * size.width, currentAnimatedFrame.y * size.height, size.width, size.height};
	SDL_Rect dstRect = { center.x - (size.width / 2), center.y - (size.height / 2), size.width, size.height };
	SDL_RendererFlip flip = DirectionX == CHAR_DIRECTION_X::Left ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;
	SDL_RenderCopyEx(renderer, texture, &srcRect, &dstRect, 0, nullptr, flip);
}