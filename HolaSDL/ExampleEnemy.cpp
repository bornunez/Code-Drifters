#include "ExampleEnemy.h"
#include "ChaseComponent.h"
#include "GunnerComponent.h"
#include "Game.h"
#include "Enemy.h"
#include "Camera.h"
#include "PlayState.h"



ExampleEnemy::ExampleEnemy(PlayState* playState, MainCharacter* mc) :
	Enemy(playState, mc)
{
	
	addComponent(new ChaseComponent(this, getMC(), 0.1));
}



ExampleEnemy::~ExampleEnemy()
{
}

void ExampleEnemy::render() {
	float auxX = transform.position.getX() - playState->getCamera()->getTransform()->position.getX();
	float auxY = transform.position.getY() - playState->getCamera()->getTransform()->position.getY();
	SDL_Rect rect RECT(auxX, auxY, transform.body.w, transform.body.h);
	SDL_SetRenderDrawColor(game->getRenderer(), COLOR(0x00ff00fff));
	SDL_RenderFillRect(game->getRenderer(), &rect);
	SDL_SetRenderDrawColor(game->getRenderer(), COLOR(0x045000ff));
}
