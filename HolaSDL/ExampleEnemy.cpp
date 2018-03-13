#include "ExampleEnemy.h"
#include "ChaseComponent.h"
#include "GunnerComponent.h"
#include "GunnerShotComponent.h"
#include "Game.h"
#include "Enemy.h"
#include "Camera.h"
#include "PlayState.h"
#include "GameObject.h"
#include "ComponentContainer.h"
#include "EnemyManager.h"


ExampleEnemy::ExampleEnemy(MainCharacter* mc) :	Enemy(mc)
{
	type = Stalker;
	this->addComponent(new ChaseComponent(this, getMC(), 0.1));

	//Gunner
	//this->addComponent(new GunnerComponent(this, getMC(), 0.1, 300));
	//this->addComponent(new GunnerShotComponent(this, getMC(), 0.1, 300));
}



ExampleEnemy::~ExampleEnemy()
{
}

void ExampleEnemy::render() {
	float auxX = transform.position.getX() - playState->getCamera()->getTransform()->position.getX();
	float auxY = transform.position.getY() - playState->getCamera()->getTransform()->position.getY();
	SDL_Rect rect RECT(auxX, auxY, transform.body.w, transform.body.h);
	SDL_SetRenderDrawColor(Game::getGame()->getRenderer(), COLOR(0x00ff00fff));
	SDL_RenderFillRect(Game::getGame()->getRenderer(), &rect);
	SDL_SetRenderDrawColor(Game::getGame()->getRenderer(), COLOR(0x045000ff));
}
