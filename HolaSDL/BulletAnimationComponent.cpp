#include "BulletAnimationComponent.h"
#include "GameObject.h"
#include "Transform.h"
#include "Game.h"
#include "PlayState.h"
#include "Camera.h"
#include "MainCharacter.h"
#include "Bullet.h"
BulletAnimationComponent::BulletAnimationComponent(Bullet * o, Texture * texture, double angle, int fps, SDL_RendererFlip flip) : RenderComponent(o)
{
	bullet = o;
	this->texture = texture;
	this->angle = angle;
	this->fps = fps;
	this->flip = flip;
}

BulletAnimationComponent::~BulletAnimationComponent()
{
}

void BulletAnimationComponent::render()
{
	angle = bullet->getAngle();
	Uint32 ticks = SDL_GetTicks();
	
	float displayX = gameObject->getDisplayPos().getX();
	float displayY = gameObject->getDisplayPos().getY();

	Uint32 sprite = (ticks / fps) % texture->getNumCols();
	SDL_Rect srcrect = { sprite * texture->getFrameWidth(), 0, texture->getFrameWidth(), texture->getFrameHeight() };
	SDL_Rect dstrect = { displayX, displayY, gameObject->getTransform()->body.w,  gameObject->getTransform()->body.h };	
	
	SDL_Point center;
	center.x = dstrect.w / 2;
	center.y = dstrect.h / 2;

	texture->render(dstrect, angle, &center, &srcrect);
}

void BulletAnimationComponent::receiveMessage(Message * msg)
{
}

float BulletAnimationComponent::getSpriteAngle()
{

	MainCharacter* mc = PlayState::getInstance()->getMainCharacter();

	Vector2D mcDisplayPos = mc->getDisplayCenterPos();

	Vector2D gunPosition = gameObject->getDisplayCenterPos();


	float angle = (atan2(mcDisplayPos.getY() - gunPosition.getY(),  mcDisplayPos.getX() - gunPosition.getX()));//Angulo entre el cursor y el jugador, en grados

	angle = angle * 180 / M_PI;
	if (angle < 0)
		angle += 360;

	return angle;
}
