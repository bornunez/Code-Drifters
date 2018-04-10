#include "HookAnimationComponent.h"
#include "GameObject.h"
#include "PlayState.h"
#include "Camera.h"
#include "Game.h"
#include "Hook.h"


HookAnimationComponent::HookAnimationComponent(Hook* o) : RenderComponent(static_cast<GameObject*>(o))
{
	hook = o;
}


void HookAnimationComponent::render()
{
	if (hook->isActive()) {

		PlayState* playState = PlayState::getInstance();
		float auxX = gameObject->getTransform()->position.getX() - playState->getCamera()->getTransform()->position.getX();
		float auxY = gameObject->getTransform()->position.getY() - playState->getCamera()->getTransform()->position.getY();
		SDL_Rect rect RECT(auxX, auxY, gameObject->getTransform()->body.w, gameObject->getTransform()->body.h);
		SDL_SetRenderDrawColor(Game::getGame()->getRenderer(), COLOR(0x00055222));
		SDL_RenderFillRect(Game::getGame()->getRenderer(), &rect);
		SDL_SetRenderDrawColor(Game::getGame()->getRenderer(), COLOR(0x00012355));
	}

}

HookAnimationComponent::~HookAnimationComponent()
{
}
