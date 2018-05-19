#pragma once
#include "EnemyBomber.h"
#include "ExampleRender.h"
#include "Game.h"
#include "Enemy.h"
#include "Camera.h"
#include "PlayState.h"
#include "GameObject.h"
#include "ComponentContainer.h"
#include "EnemyManager.h"
#include "Tileset.h"
#include "ResourceManager.h"
#include "AnimationParser.h"
#include "BasicMovement.h"
#include "BoxRenderer.h"
#include "DamageableEnemyComponent.h"
#include "BomberComponent.h"
#include "BomberShotComponent.h"
#include "BomberAnimationComponent.h"
#include "KnockbackComponent.h"
#include "StunComponent.h"
#include "AcidDeathComponent.h"


EnemyBomber::EnemyBomber(MainCharacter* mc) :	Enemy(mc)
{
	type = Bomber;
	transform.body.w = transform.body.h = 96;
	loadAnimations();
	

	setCollisionsLayers({ "Paredes","Aire", "Acido" });
	this->addComponent(new BasicMovement(this));
	this->addComponent(new BomberAnimationComponent(this, getMC(), animations, .2));
	this->addComponent(new BomberShotComponent(this, getMC(), 200, 3));
	this->addComponent(new BomberComponent(this, getMC(), 200));
	addComponent(new KnockbackComponent(this, 1000));
	addComponent(new BoxRenderer(this, playState->getCamera()));
	addComponent(new DamageableEnemyComponent(this, getMC(), .2));
	addComponent(new StunComponent(this, 0));
	addComponent(new AcidDeathComponent(this));
}


EnemyBomber::~EnemyBomber()
{
}

void EnemyBomber::loadAnimations()
{
	string animationPath = "../Animations/Enemies/BomberAnimation.tmx";
	Tileset* tileset = ResourceManager::getInstance()->getEnemyTileset(5);

	Animation* runRight = AnimationParser::parseAnimation(tileset, animationPath, "RunRight", this, 0, 0, true, 0.1);
	Animation* runLeft = AnimationParser::parseAnimation(tileset, animationPath, "RunLeft", this, 0, 0, true, 0.1);

	Animation* attackRight = AnimationParser::parseAnimation(tileset, animationPath, "AttackRight", this, 0, 0, true, 0.2);
	Animation* attackLeft = AnimationParser::parseAnimation(tileset, animationPath, "AttackLeft", this, 0, 0, true, 0.2);

	Animation* hurtRight = AnimationParser::parseAnimation(tileset, animationPath, "HurtRight", this, 0, 0, false, 0.2);
	Animation* hurtLeft = AnimationParser::parseAnimation(tileset, animationPath, "HurtLeft", this, 0, 0, false, 0.2);

	Animation* stunRight = AnimationParser::parseAnimation(tileset, animationPath, "StunRight", this, 0, 0, true, 0.2);
	Animation* stunLeft = AnimationParser::parseAnimation(tileset, animationPath, "StunLeft", this, 0, 0, true, 0.2);

	Animation* deathRight = AnimationParser::parseAnimation(tileset, animationPath, "DeathRight", this, 0, 0, false, 0.2);
	Animation* deathLeft = AnimationParser::parseAnimation(tileset, animationPath, "DeathLeft", this, 0, 0, false, 0.2);

	animations.emplace("RUNRIGHT", runRight);
	animations.emplace("RUNLEFT", runLeft);

	animations.emplace("ATTACKRIGHT", attackRight);
	animations.emplace("ATTACKLEFT", attackLeft);

	animations.emplace("HURTRIGHT", hurtRight);
	animations.emplace("HURTLEFT", hurtLeft);

	animations.emplace("STUNRIGHT", stunRight);
	animations.emplace("STUNLEFT", stunLeft);

	animations.emplace("DEATHRIGHT", deathRight);
	animations.emplace("DEATHLEFT", deathLeft);
}

void EnemyBomber::spawn(int x, int y, Spawner * spawner)
{
	Enemy::spawn(x, y, spawner);
	enemyState = EnemyState::Idle;
	Message msg(RUN_LEFT);
	sendMessage(&msg);
}
