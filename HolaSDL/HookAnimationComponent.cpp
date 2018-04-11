#include "HookAnimationComponent.h"
#include "GameObject.h"
#include "PlayState.h"
#include "MainCharacter.h"
#include "Camera.h"
#include "Game.h"
#include "Hook.h"


HookAnimationComponent::HookAnimationComponent(Hook* o, Texture* hookChainTex, Texture* hookHeadTex, double angle, int fps, SDL_RendererFlip flip) : RenderComponent(static_cast<GameObject*>(o))
{
	hook = o;
	this->hookChainTex = hookChainTex;
	this->hookHeadTex = hookHeadTex;
	this->angle = angle;
	this->fps = fps;
	this->flip = flip;
}


void HookAnimationComponent::render()
{
	if (hook->isActive()) {
		renderHookChains();
		renderHookHead();
	}

}

void HookAnimationComponent::renderHookHead()
{
	Uint32 ticks = SDL_GetTicks();

	float displayX = hook->getDisplayCenterPos().getX();
	float displayY = hook->getDisplayCenterPos().getY();

	Uint32 sprite = (ticks / fps) % hookHeadTex->getNumCols();
	SDL_Rect srcrect = { sprite * hookHeadTex->getFrameWidth(), animationNumber * hookHeadTex->getFrameHeight(), hookHeadTex->getFrameWidth(), hookHeadTex->getFrameHeight() };
	//SDL_Rect dstrect = { displayX-hook->getTransform()->body.w/2, displayY - hook->getTransform()->body.h/2, hookHeadTex->getFrameWidth() * Game::getGame()->getScale(), hookHeadTex->getFrameHeight() * Game::getGame()->getScale() };
	SDL_Rect dstrect = { displayX - hook->getTransform()->body.w / 2, displayY - hook->getTransform()->body.h / 2, hook->getTransform()->body.w,  hook->getTransform()->body.h};
	angle = hook->getAngle();

	SDL_Point center;
	center.x = dstrect.w / 2;
	center.y = dstrect.h / 2;

	hookHeadTex->render(dstrect, angle, &center, &srcrect);
}

void HookAnimationComponent::renderHookChains()
{
	Uint32 ticks = SDL_GetTicks();

	Vector2D hookSize = hook->getCenterPos() - PlayState::getInstance()->getMainCharacter()->getCenterPos();
	float hookLength = hookSize.magnitude();
	float auxX = gameObject->getTransform()->position.getX() - PlayState::getInstance()->getCamera()->getTransform()->position.getX();
	float auxY = gameObject->getTransform()->position.getY() - PlayState::getInstance()->getCamera()->getTransform()->position.getY();
	
	Uint32 sprite = (ticks / fps) % hookChainTex->getNumCols();
	SDL_Rect srcrect = { sprite * hookChainTex->getFrameWidth(), animationNumber * hookChainTex->getFrameHeight(), hookLength, hookChainTex->getFrameHeight() };
	SDL_Rect dstrect = { PlayState::getInstance()->getMainCharacter()->getDisplayCenterPos().getX(), PlayState::getInstance()->getMainCharacter()->getDisplayCenterPos().getY() - srcrect.h/2 , srcrect.w*Game::getGame()->getScale()/3, srcrect.h*Game::getGame()->getScale() / 3 };
	angle = hook->getAngle();


	Vector2D displayPosition;//Posición del personaje relativa a la cámara
	displayPosition = hook->getDisplayCenterPos();

	float angle = (atan2(displayPosition.getY() - PlayState::getInstance()->getMainCharacter()->getDisplayCenterPos().getY(), displayPosition.getX()- PlayState::getInstance()->getMainCharacter()->getDisplayCenterPos().getX()));//Angulo entre el cursor y el jugador, en grados

	angle = angle * 180 / M_PI;
	if (angle < 0)
		angle += 360;


	SDL_Point center;
	center.x = 0;
	center.y = dstrect.h / 2;

	hookChainTex->render(dstrect, angle, &center, &srcrect);
}

void HookAnimationComponent::setAngle(float angle)
{
	this->angle = angle;
}

void HookAnimationComponent::setFlip(SDL_RendererFlip flip)
{
	this->flip = flip;
}

HookAnimationComponent::~HookAnimationComponent()
{
}
