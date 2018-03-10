#include "AnimationFrame.h"
#include "GameObject.h"
#include "Texture.h"
#include "PlayStateObject.h"
#include "Camera.h"
#include "PlayState.h"
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
	destRect.x = gameObject->getTransform()->position.getX() - dynamic_cast<PlayStateObject*>(gameObject)->getPlayState()->getCamera()->getTransform()->position.getX();
	destRect.y = gameObject->getTransform()->position.getY() - dynamic_cast<PlayStateObject*>(gameObject)->getPlayState()->getCamera()->getTransform()->position.getY();

	gameObject->getTexture()->render(destRect,srcRect);	
}
