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

void AnimationFrame::setHurtbox(SDL_Rect rect, int hurtboxOffsetX , int hurtboxOffsetY )
{
	hurtbox = rect;
	this->hurtboxOffsetX = hurtboxOffsetX;
	this->hurtboxOffsetY = hurtboxOffsetY;
}

void AnimationFrame::setHitbox(SDL_Rect rect, int hitboxOffsetX, int hitboxOffsetY)
{
	hitbox = rect;
	this->hitboxOffsetX = hitboxOffsetX;
	this->hitboxOffsetY = hitboxOffsetY;
}

void AnimationFrame::render()
{
	destRect.x = gameObject->getTransform()->position.getX() - dynamic_cast<PlayStateObject*>(gameObject)->getPlayState()->getCamera()->getTransform()->position.getX();
	destRect.y = gameObject->getTransform()->position.getY() - dynamic_cast<PlayStateObject*>(gameObject)->getPlayState()->getCamera()->getTransform()->position.getY();
	updateBoxPosition();
	gameObject->getTexture()->render(destRect,srcRect);	
}

void AnimationFrame::updateBoxPosition()//Actualiza la posición de las boxes respecto al personaje
{
	hitbox.x = gameObject->getTransform()->position.getX() + hitboxOffsetX;
	hitbox.y = gameObject->getTransform()->position.getY() + hitboxOffsetY;

	hurtbox.x = gameObject->getTransform()->position.getX() + hurtboxOffsetX;
	hurtbox.y = gameObject->getTransform()->position.getY() + hurtboxOffsetY;

}
