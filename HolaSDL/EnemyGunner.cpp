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
#include "AnimationParser.h"
#include "GunnerAnimationComponent.h"
#include "Tileset.h"
#include "ResourceManager.h"


EnemyGunner::EnemyGunner(MainCharacter* mc) :	Enemy(mc)
{
	type = Stalker;
	transform.body.w = transform.body.h = 30;
	loadAnimations();
	//this->addComponent(new ExampleRender(this));
	this->addComponent(new GunnerComponent(this, getMC(), 0.1, 300));
	this->addComponent(new GunnerShotComponent(this, getMC(), 0.1, 300));
	animComp = new GunnerAnimationComponent(this, animations);
	addComponent(animComp);
}



EnemyGunner::~EnemyGunner()
{
}

void EnemyGunner::loadAnimations()
{
	string animationPath = "../Animations/Enemies/Gunner.tmx";
	Tileset* tileset = Game::getGame()->getResourceManager()->getEnemyTileset(0);
	Animation* runBot = AnimationParser::parseAnimation(tileset,animationPath, "RunBot", this);
	Animation* runTop = AnimationParser::parseAnimation(tileset, animationPath, "RunTop", this);
	Animation* runRight = AnimationParser::parseAnimation(tileset, animationPath, "RunRight", this);
	Animation* runLeft = AnimationParser::parseAnimation(tileset, animationPath, "RunLeft", this);

	animations.emplace("RUN_BOT", runBot);
	animations.emplace("RUN_TOP", runTop);
	animations.emplace("RUN_RIGHT", runRight);
	animations.emplace("RUN_LEFT", runLeft);
}

