#include "EnemyGunner.h"
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


EnemyGunner::EnemyGunner(MainCharacter* mc) :	Enemy(mc)
{
	type = Stalker;
	transform.body.w = transform.body.h = 30;
	this->addComponent(new ExampleRender(this));
	this->addComponent(new GunnerComponent(this, getMC(), 0.1, 300));
	this->addComponent(new GunnerShotComponent(this, getMC(), 0.1, 300));
}



EnemyGunner::~EnemyGunner()
{
}

