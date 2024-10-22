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
#include "KnockbackComponent.h"
#include "StunComponent.h"
#include "AcidDeathComponent.h"
#include "SkeletonRenderer.h"
EnemyGunner::EnemyGunner(MainCharacter* mc) :	Enemy(mc)
{
	type = Gunner;	
	transform.body.w = 96 / 2;
	transform.body.h = 96 / 2.5;
	setSpriteOffset(0, -8 * Game::getGame()->getScale());

	transform.overlapCollision.overlapBody.w = 96 / 5;
	transform.overlapCollision.overlapBody.h = 96 / 1.2;

	transform.overlapCollision.overlapOffset.setX(4);
	transform.overlapCollision.overlapOffset.setY(-14);
	loadAnimations();
	addComponent(new GunnerComponent(this, getMC(), 400));
	addComponent(new GunnerShotComponent(this, getMC(), 400, 2));
	setCollisionsLayers({ "Paredes","Aire", "Acido" });
	addComponent(new KnockbackComponent(this, 1000));
	addComponent(new BasicMovement(this));
	addComponent(new DamageableEnemyComponent(this, getMC(),0.2));
	addComponent(new GunnerAnimationComponent(this, getMC(), animations));
	addComponent(new StunComponent(this, 0));
	addComponent(new AcidDeathComponent(this));
	//addComponent(new SkeletonRendered(this, playState->getCamera()));
	//addComponent(new BoxRenderer(this, playState->getCamera()));*/
}



EnemyGunner::~EnemyGunner()
{
}

void EnemyGunner::loadAnimations()
{
	string animationPath = "../Animations/Enemies/GunnerAnimation.tmx";
	Tileset* tileset = ResourceManager::getInstance()->getEnemyTileset(0);
	Animation* runBot = AnimationParser::parseAnimation(tileset,animationPath, "RunBot", this);
	Animation* runTop = AnimationParser::parseAnimation(tileset, animationPath, "RunTop", this);
	Animation* runRight = AnimationParser::parseAnimation(tileset, animationPath, "RunRight", this);
	Animation* runLeft = AnimationParser::parseAnimation(tileset, animationPath, "RunLeft", this);

	animations.emplace("RUN_BOT", runBot);
	animations.emplace("RUN_TOP", runTop);
	animations.emplace("RUN_RIGHT", runRight);
	animations.emplace("RUN_LEFT", runLeft);

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

	Animation* stunRight1 = AnimationParser::parseAnimation(tileset, animationPath, "StunRight1", this, 0, 0, true, 0.15);
	Animation* stunRight2 = AnimationParser::parseAnimation(tileset, animationPath, "StunRight2", this, 0, 0, true, 0.15);
	Animation* stunLeft1 = AnimationParser::parseAnimation(tileset, animationPath, "StunLeft1", this, 0, 0, true, 0.15);
	Animation* stunLeft2 = AnimationParser::parseAnimation(tileset, animationPath, "StunLeft2", this, 0, 0, true, 0.15);

	animations.emplace("STUN_RIGHT1", stunRight1);
	animations.emplace("STUN_RIGHT2", stunRight2);
	animations.emplace("STUN_LEFT1", stunLeft1);
	animations.emplace("STUN_LEFT2", stunLeft2);

	Animation* damageRight1 = AnimationParser::parseAnimation(tileset, animationPath, "DamageRight1", this, 0, 0, false, 0.15);
	Animation* damageRight2 = AnimationParser::parseAnimation(tileset, animationPath, "DamageRight2", this, 0, 0, false, 0.15);
	Animation* damageLeft1 = AnimationParser::parseAnimation(tileset, animationPath, "DamageLeft1", this, 0, 0, false, 0.15);
	Animation* damageLeft2 = AnimationParser::parseAnimation(tileset, animationPath, "DamageLeft2", this, 0, 0, false, 0.15);

	animations.emplace("DAMAGE_RIGHT1", damageRight1);
	animations.emplace("DAMAGE_RIGHT2", damageRight2);
	animations.emplace("DAMAGE_LEFT1", damageLeft1);
	animations.emplace("DAMAGE_LEFT2", damageLeft2);

	Animation* deathRight = AnimationParser::parseAnimation(tileset, animationPath, "DeathRight", this, 0, 0, false, 0.10);
	Animation* deathLeft = AnimationParser::parseAnimation(tileset, animationPath, "DeathLeft", this, 0, 0, false, 0.10);

	animations.emplace("DEATH_RIGHT", deathRight);
	animations.emplace("DEATH_LEFT", deathLeft);
}


