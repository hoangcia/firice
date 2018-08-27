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
		currentAnimatedFrame.x = (currentAnimatedFrame.x + 1) % 4;
		currentAnimatedFrame.y = (static_cast<int>(log2(Status)));
		LastTime = currentTime;
	}
}
void Mage::update(unsigned long currentTime, std::queue<GameEvent> events, bool revertMoving)
{
	float deltaTime = (currentTime - LastTime) / 1000.0f;
	float ax = 0.0f;

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
				Status = CHARACTER_STATUS::Running;
				ax = event.Parameters["ax"];
				Direction = static_cast<CHAR_DIRECTION>(static_cast<int>(event.Parameters["direction"]));				

				Acceleration = ax;
			
				break;
			
				
			case GAME_EVENT_TYPE::CharacterJump:
				//VelocityY = event.Parameters["jumpingVelocity"];

				break;

			default: break;
		}
		events.pop();
	}

	/*Update movement velocity*/
	if (revertMoving) Direction = static_cast<CHAR_DIRECTION>(-1 * Direction);

	VelocityX += Acceleration;

	if (VelocityX < 0.0f) {
		VelocityX = 0.0f;
		Acceleration = 0.0f;
		Status = CHARACTER_STATUS::Idle;
	}
	else if (VelocityX > CHAR_MAX_VELOCITY)
	{
		VelocityX = CHAR_MAX_VELOCITY;
	}
	/*Update jumping velocity*/
	//VelocityY += deltaTime*GAME_GRAVITY;

	/*Set new position*/
	Point2 newPos = { center.x + deltaTime * VelocityX * Direction , center.y + deltaTime*VelocityY};
	//check round border
	if (newPos.x > (size.width / 2) &&		
		newPos.x + size.width / 2 < DEFAULT_SCREEN_WIDTH		
		)
	{		
		setCenter(newPos.x, center.y);
	}
	else
	{
		Acceleration = 0.0f;
		VelocityX = 0.0f;
		Status = CHARACTER_STATUS::Idle;
	}

	if(newPos.y > (size.height / 2) && 
		newPos.y + size.height / 2 < DEFAULT_SCREEN_HEIGHT)
	
	{
		setCenter(center.x, newPos.y);
	}
	else
	{
		VelocityY = 0.0f;		
	}
	
	update(currentTime);
}
void Mage::draw(SDL_Renderer* renderer, SDL_Texture* texture) {
	SDL_Rect srcRect = { currentAnimatedFrame.x * size.width, currentAnimatedFrame.y * size.height, size.width, size.height};
	SDL_Rect dstRect = { center.x - (size.width / 2), center.y - (size.height / 2), size.width, size.height };
	SDL_RendererFlip flip = Direction == CHAR_DIRECTION::Left ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;
	SDL_RenderCopyEx(renderer, texture, &srcRect, &dstRect, 0, nullptr, flip);
}