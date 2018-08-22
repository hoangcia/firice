#include "Mage.h"
#include "Constants.h"


Mage::Mage()
{
	currentAnimatedFrame = Point2{ 0,0 };
	
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
	
	if (currentTime - LastTime > 1000 / LIMIT_ANIMATED_FPS) {
		currentAnimatedFrame.x = (currentAnimatedFrame.x + 1) % 4;
		LastTime = currentTime;
	}
}
void  Mage::draw(SDL_Renderer* renderer, SDL_Texture* texture, SDL_RendererFlip flip) {
	SDL_Rect srcRect = { currentAnimatedFrame.x * size.width, currentAnimatedFrame.y * size.height, size.width, size.height};
	SDL_Rect dstRect = { center.x - (size.width / 2), center.y - (size.height / 2), size.width, size.height };

	SDL_RenderCopyEx(renderer, texture, &srcRect, &dstRect, 0, nullptr, flip);
}