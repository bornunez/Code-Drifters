#include "EnemyTurret.h"
#include "TurretShotComponent.h"
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
#include "BoxRenderer.h"

EnemyTurret::EnemyTurret(MainCharacter* mc) :	Enemy(mc)
{
	type = Gunner;
	transform.body.w = transform.body.h = 96;
	loadAnimations();
	defense = 30;
	this->addComponent(new TurretShotComponent(this, getMC(), 500, .3));
	addComponent(new BoxRenderer(this, playState->getCamera()));
	addComponent(new GunnerAnimationComponent(this, getMC(), animations));
}



EnemyTurret::~EnemyTurret()
{
}

void EnemyTurret::loadAnimations()
{
	string animationPath = "../Animations/Enemies/GunnerAnimation.tmx";
	Tileset* tileset = ResourceManager::getInstance()->getEnemyTileset(0);

	Animation* idleBot = AnimationParser::parseAnimation(tileset, animationPath, "IdleBot", this);
	Animation* idleTop = AnimationParser::parseAnimation(tileset, animationPath, "IdleTop", this);
	Animation* idleRight = AnimationParser::parseAnimation(tileset, animationPath, "IdleRight", this);
	Animation* idleLeft = AnimationParser::parseAnimation(tileset, animationPath, "IdleLeft", this);
	Animation* idleBotLeft = AnimationParser::parseAnimation(tileset, animationPath, "IdleBotLeft", this);
	Animation* idleTopLeft = AnimationParser::parseAnimation(tileset, animationPath, "IdleTopLeft", this);
	Animation* idleBotRight = AnimationParser::parseAnimation(tileset, animationPath, "IdleBotRight", this);
	Animation* idleTopRight = AnimationParser::parseAnimation(tileset, animationPath, "IdleTopRight", this);

	animations.emplace("IDLE_BOT", idleBot);
	animations.emplace("IDLE_TOP", idleTop);
	animations.emplace("IDLE_RIGHT", idleRight);
	animations.emplace("IDLE_LEFT", idleLeft);
	animations.emplace("IDLE_BOTLEFT", idleBotLeft);
	animations.emplace("IDLE_TOPLEFT", idleTopLeft);
	animations.emplace("IDLE_BOTRIGHT", idleBotRight);
	animations.emplace("IDLE_TOPRIGHT", idleTopRight);

	Animation* shotBot = AnimationParser::parseAnimation(tileset, animationPath, "ShotBot", this,0,0,false,0.15);
	Animation* shotTop = AnimationParser::parseAnimation(tileset, animationPath, "ShotTop", this,0, 0, false, 0.15);
	Animation* shotRight = AnimationParser::parseAnimation(tileset, animationPath, "ShotRight", this, 0, 0, false, 0.15);
	Animation* shotLeft = AnimationParser::parseAnimation(tileset, animationPath, "ShotLeft", this, 0, 0, false, 0.15);
	Animation* shotBotLeft = AnimationParser::parseAnimation(tileset, animationPath, "ShotBotLeft", this, 0, 0, false, 0.15);
	Animation* shotTopLeft = AnimationParser::parseAnimation(tileset, animationPath, "ShotTopLeft", this, 0, 0, false, 0.15);
	Animation* shotBotRight = AnimationParser::parseAnimation(tileset, animationPath, "ShotBotRight", this, 0, 0, false, 0.15);
	Animation* shotTopRight = AnimationParser::parseAnimation(tileset, animationPath, "ShotTopRight", this, 0, 0, false, 0.15);

	animations.emplace("SHOT_BOT", shotBot);
	animations.emplace("SHOT_TOP", shotTop);
	animations.emplace("SHOT_RIGHT", shotRight);
	animations.emplace("SHOT_LEFT", shotLeft);
	animations.emplace("SHOT_BOTLEFT", shotBotLeft);
	animations.emplace("SHOT_TOPLEFT", shotTopLeft);
	animations.emplace("SHOT_BOTRIGHT", shotBotRight);
	animations.emplace("SHOT_TOPRIGHT", shotTopRight);
}


