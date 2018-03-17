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
#include "StalkerAnimationComponent.h"
#include "Tileset.h"
#include "ResourceManager.h"
#include "AnimationParser.h"

EnemyStalker::EnemyStalker(MainCharacter* mc) :	Enemy(mc)
{
	type = Stalker;
	transform.body.w = transform.body.h = 30;
	loadAnimations();
	this->addComponent(new ExampleRender(this));
	this->addComponent(new ChaseComponent(this, getMC(), 0.1));
	animComp = new StalkerAnimationComponent(this, animations);
	addComponent(animComp);
	
}



EnemyStalker::~EnemyStalker()
{
}

void EnemyStalker::loadAnimations()
{
	string animationPath = "../Animations/Enemies/StalkerAnimation.tmx";
	Tileset* tileset = Game::getGame()->getResourceManager()->getEnemyTileset(1);
	Animation* run = AnimationParser::parseAnimation(tileset, animationPath, "Run", this);
	Animation* attack = AnimationParser::parseAnimation(tileset, animationPath, "Attack", this);

	animations.emplace("RUN", run);
	animations.emplace("ATTACK", attack);
}

