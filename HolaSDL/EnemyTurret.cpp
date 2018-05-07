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
#include "TurretAnimationComponent.h"
#include "Tileset.h"
#include "ResourceManager.h"
#include "BoxRenderer.h"

EnemyTurret::EnemyTurret(MainCharacter* mc) :	Enemy(mc)
{
	type = Turret;
	transform.body.w = 96 / 2;
	transform.body.h = 96 / 2;
	setSpriteOffset(0, 0 * Game::getGame()->getScale());

	transform.overlapBody.w = 96 / 2.1;
	transform.overlapBody.h = 96 / 1.5;

	transform.overlapOffset.setX(0);
	transform.overlapOffset.setY(0);
	loadAnimations();

	this->addComponent(new TurretShotComponent(this, getMC(), 500, 1));
	addComponent(new TurretAnimationComponent(this, getMC(), animations));
	addComponent(new SkeletonRendered(this, playState->getCamera()));
}



EnemyTurret::~EnemyTurret()
{
}

void EnemyTurret::loadAnimations()
{
	string animationPath = "../Animations/Enemies/TurretAnimation.tmx";
	Tileset* tileset = ResourceManager::getInstance()->getEnemyTileset(2);

	Animation* bot = AnimationParser::parseAnimation(tileset, animationPath, "Bot", this);
	Animation* top = AnimationParser::parseAnimation(tileset, animationPath, "Top", this);
	Animation* right = AnimationParser::parseAnimation(tileset, animationPath, "Right", this);
	Animation* left = AnimationParser::parseAnimation(tileset, animationPath, "Left", this);
	Animation* botLeft = AnimationParser::parseAnimation(tileset, animationPath, "BotLeft", this);
	Animation* topLeft = AnimationParser::parseAnimation(tileset, animationPath, "TopLeft", this);
	Animation* botRight = AnimationParser::parseAnimation(tileset, animationPath, "BotRight", this);
	Animation* topRight = AnimationParser::parseAnimation(tileset, animationPath, "TopRight", this);

	animations.emplace("BOT", bot);
	animations.emplace("TOP", top);
	animations.emplace("RIGHT", right);
	animations.emplace("LEFT", left);
	animations.emplace("BOTLEFT", botLeft);
	animations.emplace("TOPLEFT", topLeft);
	animations.emplace("BOTRIGHT", botRight);
	animations.emplace("TOPRIGHT", topRight);

	Animation* preparing = AnimationParser::parseAnimation(tileset, animationPath, "Preparing", this,0,0,false,0.15);
	Animation* disambling = AnimationParser::parseAnimation(tileset, animationPath, "Disambling", this, 0, 0, false, 0.15);
	Animation* waiting = AnimationParser::parseAnimation(tileset, animationPath, "Waiting", this, 0, 0, true, 0.15);

	animations.emplace("PREPARING", preparing);
	animations.emplace("DISAMBLING", disambling);
	animations.emplace("WAITING", waiting);

	
}


