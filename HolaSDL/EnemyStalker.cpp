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
#include "KnockbackComponent.h"
#include "StalkerComponent.h"
#include "StunComponent.h"
#include "SkeletonRenderer.h"
#include "AcidDeathComponent.h"

EnemyStalker::EnemyStalker(MainCharacter* mc) :	Enemy(mc)
{
	type = Stalker;
	transform.body.w = 96 / 3;
	transform.body.h = 96 / 1.3;

	setSpriteOffset(1 * Game::getGame()->getScale(), 0 * Game::getGame()->getScale());

	transform.overlapCollision.overlapBody.w = 96 / 3;
	transform.overlapCollision.overlapBody.h = 96 / 1.3;

	transform.overlapCollision.overlapOffset.setX(0);
	transform.overlapCollision.overlapOffset.setY(0);


	loadAnimations();
	facing = RIGHT;
	setCollisionsLayers({ "Paredes","Aire", "Acido" });
	this->addComponent(new KnockbackComponent(this, 1000));
	this->addComponent(new BasicMovement(this));
	this->addComponent(new DamageableEnemyComponent(this, getMC(),.2));
	//parametros: tiempo entre cargas, tiempo de delay al cargar, tiempo de movimiento en carga, multiplicador velocidad
	this->addComponent(new StalkerComponent(this, getMC(), 4, .5, 1, 1.2));
	this->addComponent(new StalkerAnimationComponent(this, getMC(), animations, .2, .5));
	this->addComponent(new StunComponent(this, 0));
	addComponent(new AcidDeathComponent(this));
	//addComponent(new SkeletonRendered(this,playState->getCamera()));
	//addComponent(new BoxRenderer(this, playState->getCamera()));*/

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
	Animation* stun = AnimationParser::parseAnimation(tileset, animationPath, "Stun", this, 0, 0, true);
	Animation* death = AnimationParser::parseAnimation(tileset, animationPath, "Death", this);
	Animation* charge = AnimationParser::parseAnimation(tileset, animationPath, "Charge", this, 0, 0, false);

	animations.emplace("RUN", run);
	animations.emplace("ATTACK", attack);
	animations.emplace("HURT", hurt);
	animations.emplace("STUN", stun);
	animations.emplace("DEATH", death);
	animations.emplace("CHARGE", charge);
}

void EnemyStalker::spawn(int x, int y, Spawner * spawner)
{
	Enemy::spawn(x, y, spawner);
	enemyState = EnemyState::Run;
	Message msg(STALKER_RUN);
	sendMessage(&msg);
}


