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
#include "StunComponent.h"
//#include "ChargeComponent.h"
//#include "ChaseComponent.h"



EnemyStalker::EnemyStalker(MainCharacter* mc) :	Enemy(mc)
{
	type = Stalker;
	transform.body.w = transform.body.h = 32*Game::getGame()->getScale();
	loadAnimations();
	facing = LEFT;
	//this->addComponent(new ChaseComponent(this, getMC()));
	//this->addComponent(new ChargeComponent(this, getMC(), 2, 1, 2));
	vector<string> collisionLayers = { "Paredes","Aire" };
	addComponent(new KnockbackComponent(this, 10000, collisionLayers));
	this->addComponent(new BasicMovement(this, collisionLayers));
	this->addComponent(new StalkerAnimationComponent(this, getMC(), animations));
	this->addComponent(new DamageableEnemyComponent(this, getMC()));
	this->addComponent(new StalkerComponent(this, getMC(), 1, 1.5, 2));
	addComponent(new BasicInvincibleComponent(this, 0.2));
	addComponent(new BoxRenderer(this, playState->getCamera()));
	addComponent(new StunComponent(this));

}


EnemyStalker::~EnemyStalker()
{
}

void EnemyStalker::loadAnimations()
{
	string animationPath = "../Animations/Enemies/StalkerAnimation.tmx";
	Tileset* tileset = ResourceManager::getInstance()->getEnemyTileset(1);
	Animation* run = AnimationParser::parseAnimation(tileset, animationPath, "Run", this);
	Animation* attack = AnimationParser::parseAnimation(tileset, animationPath, "Attack", this, 0, 0, false, 0.2);
	Animation* hurt = AnimationParser::parseAnimation(tileset, animationPath, "Hurt", this, 0, 0, false);

	animations.emplace("RUN", run);
	animations.emplace("ATTACK", attack);
	animations.emplace("HURT", hurt);
}

