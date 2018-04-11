#pragma once
#include "MainCharacter.h"
#include "Game.h"
#include "Camera.h"
#include "PlayState.h"
#include "BasicMovement.h"
#include "MCShotComponent.h"
#include "MCAttackComponent.h"
#include "SkeletonRenderer.h"
#include "Texture.h"
#include "MCAnimationComponent.h"
#include "ResourceManager.h"
#include "MCMovementInput.h"
#include "MCAttackCollisionComponent.h"
#include "AnimationParser.h"
#include "BoxRenderer.h"
#include "LevelExplorer.h"
#include "DoorsCollision.h"
#include "MCHookInputComponent.h"
#include "HookShotComponent.h"
#include "ExampleRender.h"
#include "HookAnimationComponent.h"
//Personaje principal




MainCharacter::MainCharacter(Texture * tex, int x, int y, int w, int h)
	: GameObject(tex, x, y, w, h), hook(500)
{
	transform.position.setX(x);
	transform.position.setY(y);
	transform.body.x = x; transform.body.y = y + h/2.5;
	transform.body.w = w/2;
	transform.body.h = h/2.5;

	loadAnimations();

	transform.speed = 500;
	//setMaxVelocity(0.5);

	
	addComponent(new MCMovementInput(this, SDL_SCANCODE_W, SDL_SCANCODE_D, SDL_SCANCODE_S, SDL_SCANCODE_A));
	vector<string> collisionLayer = { "Paredes","Aire" };
	addComponent(new BasicMovement(this, collisionLayer));
	addComponent(new MCShotComponent(this));
	addComponent(new MCAttackComponent(this));
	addComponent(new SkeletonRendered(this, playState->getCamera()));	
	addComponent(new MCAttackCollisionComponent(this));
	addComponent(new MCAnimationComponent(this, animations));
	addComponent(new BoxRenderer(this, playState->getCamera()));
	addComponent(new LevelExplorer(this));
	addComponent(new DoorsCollision(this));
	hookShot = new HookShotComponent(this,&hook, 1000.0f);
	addComponent(hookShot);
	addComponent(new MCHookInputComponent(this));
	addComponent(new HookAnimationComponent(&hook, ResourceManager::getInstance()->getTexture(HookChain), ResourceManager::getInstance()->getTexture(HookHead)));

	setCurrentBullets(4);
	setReloadTime(4);
	setMaxBullets(4);
	normalAttackDamage = 50;
	movable = true;
	
}

MainCharacter::~MainCharacter()
{
	//animations.clear();
}
void MainCharacter::loadAnimations()
{
	Tileset* tileset = ResourceManager::getInstance()->getProtaTileset();
	string animationPath = "../Animations/Protagonist/tileset/ProtaAnimation.tmx";
	Animation* idleBot = AnimationParser::parseAnimation(tileset, animationPath, "IdleBot", this);
	Animation* idleTop = AnimationParser::parseAnimation(tileset, animationPath, "IdleTop", this);
	Animation* idleRight = AnimationParser::parseAnimation(tileset, animationPath, "IdleRight", this);
	Animation* idleLeft = AnimationParser::parseAnimation(tileset, animationPath, "IdleLeft", this);

	animations.emplace("IDLE_BOT", idleBot);
	animations.emplace("IDLE_TOP", idleTop);
	animations.emplace("IDLE_RIGHT", idleRight);
	animations.emplace("IDLE_LEFT", idleLeft);

	Animation*runBot = AnimationParser::parseAnimation(tileset, animationPath, "RunBot", this);
	Animation*runTop = AnimationParser::parseAnimation(tileset, animationPath, "RunTop", this);
	Animation*runRight = AnimationParser::parseAnimation(tileset, animationPath, "RunRight", this);
	Animation*runLeft = AnimationParser::parseAnimation(tileset, animationPath, "RunLeft", this);

	animations.emplace("RUN_BOT", runBot);
	animations.emplace("RUN_TOP", runTop);
	animations.emplace("RUN_RIGHT", runRight);
	animations.emplace("RUN_LEFT", runLeft);

	Animation*attackRight1 = AnimationParser::parseAnimation(tileset, animationPath, "AttackRight1", this, 10*Game::getGame()->getScale(),0,false);
	Animation*attackRight2 = AnimationParser::parseAnimation(tileset, animationPath, "AttackRight2", this, 10 * Game::getGame()->getScale(),0, false);
	Animation*attackRight3 = AnimationParser::parseAnimation(tileset, animationPath, "AttackRight3", this, 10 * Game::getGame()->getScale(),0, false);

	animations.emplace("ATTACK1_RIGHT", attackRight1);
	animations.emplace("ATTACK2_RIGHT", attackRight2);
	animations.emplace("ATTACK3_RIGHT", attackRight3);

	Animation*attackLeft1 = AnimationParser::parseAnimation(tileset, animationPath, "AttackLeft1", this, -10 * Game::getGame()->getScale(),0, false);
	Animation*attackLeft2 = AnimationParser::parseAnimation(tileset, animationPath, "AttackLeft2", this, -10 * Game::getGame()->getScale(),0, false);
	Animation*attackLeft3 = AnimationParser::parseAnimation(tileset, animationPath, "AttackLeft3", this, -10 * Game::getGame()->getScale(),0, false);

	animations.emplace("ATTACK1_LEFT", attackLeft1);
	animations.emplace("ATTACK2_LEFT", attackLeft2);
	animations.emplace("ATTACK3_LEFT", attackLeft3);

	Animation*attackTopLeft1 = AnimationParser::parseAnimation(tileset, animationPath, "AttackTopLeft1", this,0, -10 * Game::getGame()->getScale(), false);
	Animation*attackTopLeft2  = AnimationParser::parseAnimation(tileset, animationPath, "AttackTopLeft2", this, 0, -10 * Game::getGame()->getScale(), false);
	Animation*attackTopLeft3 = AnimationParser::parseAnimation(tileset, animationPath, "AttackTopLeft3", this, 0, -10 * Game::getGame()->getScale(), false);

	animations.emplace("ATTACK1_TOPLEFT", attackTopLeft1);
	animations.emplace("ATTACK2_TOPLEFT", attackTopLeft2);
	animations.emplace("ATTACK3_TOPLEFT", attackTopLeft3);

	Animation*attackTopRight1  = AnimationParser::parseAnimation(tileset, animationPath, "AttackTopRight1", this, 0, -10 * Game::getGame()->getScale(), false);
	Animation*attackTopRight2 = AnimationParser::parseAnimation(tileset, animationPath, "AttackTopRight2", this, 0, -10 * Game::getGame()->getScale(), false);
	Animation*attackTopRight3 = AnimationParser::parseAnimation(tileset, animationPath, "AttackTopRight3", this, 0, -10 * Game::getGame()->getScale(), false);

	animations.emplace("ATTACK1_TOPRIGHT", attackTopRight1);
	animations.emplace("ATTACK2_TOPRIGHT", attackTopRight2);
	animations.emplace("ATTACK3_TOPRIGHT", attackTopRight3);

	Animation*attackBotRight1 = AnimationParser::parseAnimation(tileset, animationPath, "AttackBotRight1", this, 0, 0, false);
	Animation*attackBotRight2 = AnimationParser::parseAnimation(tileset, animationPath, "AttackBotRight2", this, 0, 0, false);
	Animation*attackBotRight3 = AnimationParser::parseAnimation(tileset, animationPath, "AttackBotRight3", this, 0, 0, false);

	animations.emplace("ATTACK1_BOTRIGHT", attackBotRight1);
	animations.emplace("ATTACK2_BOTRIGHT", attackBotRight2);
	animations.emplace("ATTACK3_BOTRIGHT", attackBotRight3);

	Animation*attackBotLeft1 = AnimationParser::parseAnimation(tileset, animationPath, "AttackBotLeft1", this, 0,0,false);
	Animation*attackBotLeft2 = AnimationParser::parseAnimation(tileset, animationPath, "AttackBotLeft2", this, 0, 0, false);
	Animation*attackBotLeft3 = AnimationParser::parseAnimation(tileset, animationPath, "AttackBotLeft3", this, 0, 0, false);

	animations.emplace("ATTACK1_BOTLEFT", attackBotLeft1);
	animations.emplace("ATTACK2_BOTLEFT", attackBotLeft2);
	animations.emplace("ATTACK3_BOTLEFT", attackBotLeft3);
}

//Getters & Setters

void MainCharacter::setCurrentBullets(int num)
{
	currentBullets = num;
}
int MainCharacter::getCurrentBullets()
{
	return currentBullets;
}
void MainCharacter::setMaxBullets(int bullets)
{
	maxBullets = bullets;
}
int MainCharacter::getMaxBullets()
{
	return maxBullets;
}
float MainCharacter::getNormalAttackDamage()
{
	return normalAttackDamage;
}
void MainCharacter::setNormalAttackDamage(float dmg)
{
	normalAttackDamage = dmg;
}
float MainCharacter::getChargedAttackDamage()
{
	return chargedAttackDamage;
}
void MainCharacter::setChargedAttackDamage(float dmg)
{
	chargedAttackDamage = dmg;
}
float MainCharacter::getAttackDamage(string attackType)
{
	if (attackType == "NORMAL_ATTACK") {
		return getNormalAttackDamage();
	}
	else if (attackType == "CHARGED_ATTACK") {
		return getChargedAttackDamage();
	}
	else {
		return 0.0f;
	}
}
void MainCharacter::setMaxVelocity(float vel)
{
	maxVelocity = vel;
}
float MainCharacter::getVelocity()
{
	return velocity;
}
float MainCharacter::getMaxVelocity()
{
	return maxVelocity;
}
float MainCharacter::getHP()
{
	return HP;
}
Vector2D MainCharacter::getGunPosition()
{
	return gunPosition;
}
void MainCharacter::setGunPosition(Vector2D pos)
{
	gunPosition = pos;
}
void MainCharacter::substractHP(int damage)
{
	HP -= damage;
}

int MainCharacter::getReloadTime()
{
	return reloadTime;
}

void MainCharacter::setReloadTime(int miliseconds)
{
	reloadTime = miliseconds;
}

void MainCharacter::shootHook(Vector2D originPos, Vector2D hookDir)
{
	hookShot->shoot(originPos, hookDir);
}

void MainCharacter::addHP(int life)
{
	HP += life;
}
