#pragma once
#include "EnemyCharger.h"
#include "ExampleRender.h"
#include "Game.h"
#include "Enemy.h"
#include "Camera.h"
#include "PlayState.h"
#include "GameObject.h"
#include "ComponentContainer.h"
#include "EnemyManager.h"
#include "ChargerAnimationComponent.h"
#include "Tileset.h"
#include "ResourceManager.h"
#include "AnimationParser.h"
#include "BasicMovement.h"
#include "BoxRenderer.h"
#include "BasicInvincibleComponent.h"
#include "KnockbackComponent.h"
#include "ChargerComponent.h"
#include "DamageableEnemyComponent.h"
#include "WallStunComponent.h"
//#include "ChargeComponent.h"
//#include "ChaseComponent.h"



EnemyCharger::EnemyCharger(MainCharacter* mc) :	Enemy(mc)
{
	type = Charger;
	transform.body.w = transform.body.h = 96;
	loadAnimations();
	facing = LEFTs;
	//this->addComponent(new ChaseComponent(this, getMC()));
	//this->addComponent(new ChargeComponent(this, getMC(), 2, 1, 2));
	setCollisionsLayers({ "Paredes","Aire" });
	addComponent(new KnockbackComponent(this, 10000));
	addComponent(new WallStunComponent(this, 4.0));
	this->addComponent(new BasicMovement(this));
	this->addComponent(new ChargerAnimationComponent(this, getMC(), animations));
	this->addComponent(new ChargerComponent(this, getMC(), 1, 1.5, 2));
	addComponent(new BasicInvincibleComponent(this, 100));
	addComponent(new BoxRenderer(this, playState->getCamera()));
	addComponent(new DamageableEnemyComponent(this, getMC()));
}


EnemyCharger::~EnemyCharger()
{
}

void EnemyCharger::loadAnimations()
{
	string animationPath = "../Animations/Enemies/StalkerAnimation.tmx";
	Tileset* tileset = ResourceManager::getInstance()->getEnemyTileset(1);
	Animation* run = AnimationParser::parseAnimation(tileset, animationPath, "Run", this);
	Animation* attack = AnimationParser::parseAnimation(tileset, animationPath, "Attack", this, 0, 0, false, 0.2);

	animations.emplace("RUN", run);
	animations.emplace("ATTACK", attack);
}

