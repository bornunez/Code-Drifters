#include "ExampleEnemy.h"
#include "ChaseComponent.h"
#include "GunnerComponent.h"
#include "GunnerShotComponent.h"
#include "ExampleRender.h"
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
	this->addComponent(new ExampleRender(this));
	this->addComponent(new ChaseComponent(this, getMC(), 0.1));

	//Gunner
	//this->addComponent(new GunnerComponent(this, getMC(), 0.1, 300));
	//this->addComponent(new GunnerShotComponent(this, getMC(), 0.1, 300));
}



ExampleEnemy::~ExampleEnemy()
{
}

