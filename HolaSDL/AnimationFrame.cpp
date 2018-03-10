#include "AnimationFrame.h"
#include "GameObject.h"
#include "Texture.h"

AnimationFrame::AnimationFrame(GameObject* o,SDL_Rect* srcRect, SDL_Rect destRect)
{
	gameObject = o;
	this->srcRect = srcRect;
	this->destRect = destRect;
}


AnimationFrame::~AnimationFrame()
{
}

void AnimationFrame::setHurtbox(SDL_Rect rect)
{
	hurtbox = rect;
}

void AnimationFrame::setHitbox(SDL_Rect rect)
{
	hitbox = rect;
}

void AnimationFrame::render()
{
	destRect.x = gameObject->getTransform()->position.getX();
	destRect.y = gameObject->getTransform()->position.getY();
	destRect.w = 50;
	destRect.h = 50;
	gameObject->getTexture()->render(destRect,srcRect);	
}
