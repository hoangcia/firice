#include "Mage.h"
#include "Constants.h"


Mage::Mage()
{
	currentAnimatedFrame = Point2{ 0,0 };
	LastTime = 0;
	Status = CHARACTER_STATUS::Idle;
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
void Mage::update(unsigned long currentTime, Vector2 direction)
{
	float deltaTime = (currentTime - LastTime) / 1000.0f;
	if(deltaTime > 0.05f)
	{
		deltaTime = 0.05f;
	}
	
	Point2 newPos = { center.x + deltaTime * CHAR_VELOCITY * direction.x , center.y + deltaTime * CHAR_VELOCITY * direction.y };
	//check round border
	if( newPos.x > (size.width / 2) && 
		newPos.y > (size.height / 2) &&
		newPos.x + size.width / 2 < DEFAULT_SCREEN_WIDTH &&
		newPos.y + size.height / 2 < DEFAULT_SCREEN_HEIGHT
	)
	{
		Status = CHARACTER_STATUS::Running;
		setCenter(newPos.x, newPos.y);
	}
	else
	{
		Status = CHARACTER_STATUS::Idle;
	}
	update(currentTime);
}
void  Mage::draw(SDL_Renderer* renderer, SDL_Texture* texture, SDL_RendererFlip flip) {
	SDL_Rect srcRect = { currentAnimatedFrame.x * size.width, currentAnimatedFrame.y * size.height, size.width, size.height};
	SDL_Rect dstRect = { center.x - (size.width / 2), center.y - (size.height / 2), size.width, size.height };

	SDL_RenderCopyEx(renderer, texture, &srcRect, &dstRect, 0, nullptr, flip);
}