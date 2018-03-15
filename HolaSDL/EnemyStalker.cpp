#include "EnemyStalker.h"
#include "ChaseComponent.h"
#include "ExampleRender.h"
#include "Game.h"
#include "Enemy.h"
#include "Camera.h"
#include "PlayState.h"
#include "GameObject.h"
#include "ComponentContainer.h"
#include "EnemyManager.h"


EnemyStalker::EnemyStalker(MainCharacter* mc) :	Enemy(mc)
{
	type = Stalker;
	transform.body.w = transform.body.h = 30;
	this->addComponent(new ExampleRender(this));
	this->addComponent(new ChaseComponent(this, getMC(), 0.1));

	
}



EnemyStalker::~EnemyStalker()
{
}

