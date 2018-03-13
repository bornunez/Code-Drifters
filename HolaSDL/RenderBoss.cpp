#include "RenderBoss.h"
#include "MCBulletRenderComponent.h"
#include "GameObject.h"
#include "PlayState.h"
#include "Camera.h"
#include "Game.h"


RenderBoss::RenderBoss(GameObject* o):RenderComponent(o)
{
}


RenderBoss::~RenderBoss()
{
}
void RenderBoss::render()
{
	PlayState* playState = PlayState::getInstance();
	float auxX = gameObject->getTransform()->position.getX() - playState->getCamera()->getTransform()->position.getX();
	float auxY = gameObject->getTransform()->position.getY() - playState->getCamera()->getTransform()->position.getY();
	SDL_Rect rect RECT(auxX, auxY, gameObject->getTransform()->body.w, gameObject->getTransform()->body.h);
	SDL_SetRenderDrawColor(Game::getGame()->getRenderer(), COLOR(0x5ff55fff));
	SDL_RenderFillRect(Game::getGame()->getRenderer(), &rect);
	SDL_SetRenderDrawColor(Game::getGame()->getRenderer(), COLOR(0x000ff0ff));
}
