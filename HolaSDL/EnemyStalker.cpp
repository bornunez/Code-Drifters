#pragma once
#include "EnemyStalker.h"
#include "ExampleRender.h"
#include "Game.h"
#include "Enemy.h"
#include "Camera.h"
#include "PlayState.h"
#include "GameObject.h"
#include "ComponentContainer.h"
#include "EnemyManager.h"
#include "StalkerAnimationComponent.h"
#include "Tileset.h"
#include "ResourceManager.h"
#include "AnimationParser.h"
#include "BasicMovement.h"
#include "BoxRenderer.h"
#include "DamageableEnemyComponent.h"
#include "BasicInvincibleComponent.h"
#include "KnockbackComponent.h"
#include "StalkerComponent.h"
//#include "ChargeComponent.h"
//#include "ChaseComponent.h"



EnemyStalker::EnemyStalker(MainCharacter* mc) :	Enemy(mc)
{
	type = Stalker;
	transform.body.w = transform.body.h = 96;
	loadAnimations();
	facing = LEFT;
	//this->addComponent(new ChaseComponent(this, getMC()));
	//this->addComponent(new ChargeComponent(this, getMC(), 2, 1, 2));
	addComponent(new KnockbackComponent(this, 10000, "Paredes"));
	this->addComponent(new BasicMovement(this, "Paredes"));
	this->addComponent(new StalkerAnimationComponent(this, getMC(), animations));
	this->addComponent(new DamageableEnemyComponent(this, getMC()));
	this->addComponent(new StalkerComponent(this, getMC(), 1, 1.5, 2));
	addComponent(new BasicInvincibleComponent(this, 0.2));
	addComponent(new BoxRenderer(this, playState->getCamera()));
}


EnemyStalker::~EnemyStalker()
{
}

void EnemyStalker::loadAnimations()
{
	string animationPath = "../Animations/Enemies/StalkerAnimation.tmx";
	Tileset* tileset = Game::getGame()->getResourceManager()->getEnemyTileset(1);
	Animation* run = AnimationParser::parseAnimation(tileset, animationPath, "Run", this);
	Animation* attack = AnimationParser::parseAnimation(tileset, animationPath, "Attack", this, 0, 0, false, 0.2);

	animations.emplace("RUN", run);
	animations.emplace("ATTACK", attack);
}

