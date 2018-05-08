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
#include "ChargerComponent.h"
#include "ChargerDamageableEnemyComponent.h"
#include "WallStunComponent.h"



EnemyCharger::EnemyCharger(MainCharacter* mc) :	Enemy(mc)
{
	type = Charger;
	transform.body.w = 96/2;
	transform.body.h = 96/1.3;

	setSpriteOffset(2 * Game::getGame()->getScale(), 0 * Game::getGame()->getScale());

	transform.overlapCollision.overlapBody.w = 96 / 2;
	transform.overlapCollision.overlapBody.h = 96 / 1.3;

	transform.overlapCollision.overlapOffset.setX(0);
	transform.overlapCollision.overlapOffset.setY(0);


	loadAnimations();
	
	//this->addComponent(new ChaseComponent(this, getMC()));
	//this->addComponent(new ChargeComponent(this, getMC(), 2, 1, 2));
	setCollisionsLayers({ "Paredes","Aire" });
	addComponent(new WallStunComponent(this, 4.0));
	this->addComponent(new BasicMovement(this));
	this->addComponent(new ChargerAnimationComponent(this, getMC(), animations, .2, .5));
	this->addComponent(new ChargerComponent(this, getMC(), 4, .6, 10, 2));
	addComponent(new SkeletonRendered(this, playState->getCamera()));
	addComponent(new BoxRenderer(this, playState->getCamera()));
	addComponent(new ChargerDamageableEnemyComponent(this, getMC(), 0.2));

}


EnemyCharger::~EnemyCharger()
{
}

void EnemyCharger::loadAnimations()
{
	string animationPath = "../Animations/Enemies/ChargerAnimation.tmx";
	Tileset* tileset = ResourceManager::getInstance()->getEnemyTileset(3);

	Animation* runBot = AnimationParser::parseAnimation(tileset, animationPath, "RunBot", this, 0, 0, true, 0.1);
	Animation* runRight = AnimationParser::parseAnimation(tileset, animationPath, "RunRight", this, 0, 0, true, 0.1);
	Animation* runTop = AnimationParser::parseAnimation(tileset, animationPath, "RunTop", this, 0, 0, true, 0.1);
	Animation* runLeft = AnimationParser::parseAnimation(tileset, animationPath, "RunLeft", this, 0, 0, true, 0.1);

	Animation* preChargeBot = AnimationParser::parseAnimation(tileset, animationPath, "PreChargeBot", this, 0, 0, false, 0.15);
	Animation* preChargeRight = AnimationParser::parseAnimation(tileset, animationPath, "PreChargeRight", this, 0, 0, false, 0.15);
	Animation* preChargeTop = AnimationParser::parseAnimation(tileset, animationPath, "PreChargeTop", this, 0, 0, false, 0.15);
	Animation* preChargeLeft = AnimationParser::parseAnimation(tileset, animationPath, "PreChargeLeft", this, 0, 0, false, 0.15);

	Animation* chargeBot = AnimationParser::parseAnimation(tileset, animationPath, "ChargeBot", this, 0, 0, true, 0.2);
	Animation* chargeRight = AnimationParser::parseAnimation(tileset, animationPath, "ChargeRight", this, 0, 0, true, 0.2);
	Animation* chargeTop = AnimationParser::parseAnimation(tileset, animationPath, "ChargeTop", this, 0, 0, true, 0.2);
	Animation* chargeLeft = AnimationParser::parseAnimation(tileset, animationPath, "ChargeLeft", this, 0, 0, true, 0.2);

	//Animation* hurt = AnimationParser::parseAnimation(tileset, animationPath, "Hurt", this, 0, 0, false, 0.2);
	Animation* deathRight = AnimationParser::parseAnimation(tileset, animationPath, "DeathRight", this, 0, 0, false, 0.2);
	Animation* deathLeft = AnimationParser::parseAnimation(tileset, animationPath, "DeathLeft", this, 0, 0, false, 0.2);
	Animation* stunRight = AnimationParser::parseAnimation(tileset, animationPath, "StunRight", this);
	Animation* stunLeft = AnimationParser::parseAnimation(tileset, animationPath, "StunLeft", this);


	animations.emplace("RUNBOT", runBot);
	animations.emplace("RUNRIGHT", runRight);
	animations.emplace("RUNTOP", runTop);
	animations.emplace("RUNLEFT", runLeft);

	animations.emplace("PRECHARGEBOT", preChargeBot);
	animations.emplace("PRECHARGERIGHT", preChargeRight);
	animations.emplace("PRECHARGETOP", preChargeTop);
	animations.emplace("PRECHARGELEFT", preChargeLeft);

	animations.emplace("CHARGEBOT", chargeBot);
	animations.emplace("CHARGERIGHT", chargeRight);
	animations.emplace("CHARGETOP", chargeTop);
	animations.emplace("CHARGELEFT", chargeLeft);

	//animations.emplace("HURT", hurt);
	animations.emplace("DEATHRIGHT", deathRight);
	animations.emplace("DEATHLEFT", deathLeft);
	animations.emplace("STUNRIGHT", stunRight);
	animations.emplace("STUNLEFT", stunLeft);


}

void EnemyCharger::spawn(int x, int y, Spawner * spawner)
{
	Enemy::spawn(x, y, spawner);
	enemyState = EnemyState::Run;
	Message msg(RUN_LEFT);
	sendMessage(&msg);
}

