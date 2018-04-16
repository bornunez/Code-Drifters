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
#include "SkeletonRenderer.h"
//#include "ChargeComponent.h"
//#include "ChaseComponent.h"



EnemyStalker::EnemyStalker(MainCharacter* mc) :	Enemy(mc)
{
	type = Stalker;
	transform.body.w =32*Game::getGame()->getScale()/3;
	transform.body.h = 32 * Game::getGame()->getScale() / 2;
	loadAnimations();
	facing = RIGHT;
	//this->addComponent(new ChaseComponent(this, getMC()));
	//this->addComponent(new ChargeComponent(this, getMC(), 2, 1, 2));
	setCollisionsLayers({ "Paredes","Aire" });
	addComponent(new KnockbackComponent(this, 10000));
	this->addComponent(new BasicMovement(this));
	this->addComponent(new DamageableEnemyComponent(this, getMC()));
	//parametros: tiempo entre cargas, tiempo de delay al cargar, tiempo de movimiento en carga, multiplicador velocidad
	this->addComponent(new StalkerComponent(this, getMC(), 8, .5, 1.5, 2));
	this->addComponent(new StalkerAnimationComponent(this, getMC(), animations, .2, .5));
	addComponent(new BasicInvincibleComponent(this, 0.2));
	addComponent(new BoxRenderer(this, playState->getCamera()));
	addComponent(new StunComponent(this));
	addComponent(new SkeletonRendered(this,playState->getCamera()));

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
	Animation* death = AnimationParser::parseAnimation(tileset, animationPath, "Death", this);
	Animation* charge = AnimationParser::parseAnimation(tileset, animationPath, "Charge", this, 0, 0, false);

	animations.emplace("RUN", run);
	animations.emplace("ATTACK", attack);
	animations.emplace("HURT", hurt);
	animations.emplace("DEATH", death);
	animations.emplace("CHARGE", charge);
}

