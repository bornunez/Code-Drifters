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
#include "BasicMovement.h"
#include "DamageableEnemyComponent.h"
#include "BoxRenderer.h"


EnemyGunner::EnemyGunner(MainCharacter* mc) :	Enemy(mc)
{
	type = Stalker;
	transform.body.w = transform.body.h = 96;
	loadAnimations();
	defense = 30;
	this->addComponent(new GunnerComponent(this, getMC(), 400));
	this->addComponent(new GunnerShotComponent(this, getMC(), 400, 2));
	this->addComponent(new BasicMovement(this, "Paredes"));
	this->addComponent(new DamageableEnemyComponent(this));
	addComponent(new BoxRenderer(this, playState->getCamera()));
	addComponent(new GunnerAnimationComponent(this, animations));
	
}



EnemyGunner::~EnemyGunner()
{
}

void EnemyGunner::loadAnimations()
{
	string animationPath = "../Animations/Enemies/GunnerAnimation.tmx";
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


