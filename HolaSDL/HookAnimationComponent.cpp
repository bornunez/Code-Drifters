#include "HookAnimationComponent.h"
#include "GameObject.h"
#include "PlayState.h"
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

		Uint32 ticks = SDL_GetTicks();

		float auxX = gameObject->getTransform()->position.getX() - PlayState::getInstance()->getCamera()->getTransform()->position.getX();
		float auxY = gameObject->getTransform()->position.getY() - PlayState::getInstance()->getCamera()->getTransform()->position.getY();

		Uint32 sprite = (ticks / fps) % hookHeadTex->getNumCols();
		SDL_Rect srcrect = { sprite * hookHeadTex->getFrameWidth(), animationNumber * hookHeadTex->getFrameHeight(), hookHeadTex->getFrameWidth(), hookHeadTex->getFrameHeight() };
		SDL_Rect dstrect = { auxX, auxY , hookHeadTex->getFrameWidth() * Game::getGame()->getScale(), hookHeadTex->getFrameHeight() * Game::getGame()->getScale() };
		angle = hook->getAngle();

		hookHeadTex->render(dstrect, angle, &srcrect);
	}

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
