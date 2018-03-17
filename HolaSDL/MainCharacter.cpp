#pragma once
#include "MainCharacter.h"
#include "Game.h"
#include "Camera.h"
#include "MCMovementComponent.h"
#include "PlayState.h"
#include "BasicMovement.h"
#include "MCShotComponent.h"
#include "MCAttackComponent.h"
#include "SkeletonRenderer.h"
#include "Texture.h"
#include "MCAnimationComponent.h"
#include "ResourceManager.h"
#include "MCMovementInput.h"
#include "AnimationParser.h"
//Personaje principal




MainCharacter::MainCharacter(Texture * tex, int x, int y, int w, int h)
	: GameObject(tex, x, y, w, h)
{
	transform.position.setX(x);
	transform.position.setY(y);
	transform.body.w = w;
	transform.body.h = h;

	loadAnimations();

	transform.speed = 500;
	//setMaxVelocity(0.5);

	
	addComponent(new MCMovementInput(this, SDL_SCANCODE_W, SDL_SCANCODE_D, SDL_SCANCODE_S, SDL_SCANCODE_A));
	addComponent(new MCMovementComponent(this));
	addComponent(new BasicMovement(this, "Paredes"));
	addComponent(new MCShotComponent(this));
	addComponent(new MCAttackComponent(this));
	addComponent(new SkeletonRendered(this, playState->getCamera()));
	animComp = new MCAnimationComponent(this, animations);
	addComponent(animComp);
	setCurrentBullets(4);
	setReloadTime(4);
	setMaxBullets(4);
	
	
}

MainCharacter::~MainCharacter()
{
}
void MainCharacter::loadAnimations()
{
	Tileset* tileset = Game::getGame()->getResourceManager()->getProtaTileset();
	string animationPath = "../Animations/Protagonist/tileset/ProtaAnimation.tmx";
	idleBot = AnimationParser::parseAnimation(tileset, animationPath, "IdleBot", this);
	idleTop = AnimationParser::parseAnimation(tileset, animationPath, "IdleTop", this);
	idleRight = AnimationParser::parseAnimation(tileset, animationPath, "IdleRight", this);
	idleLeft = AnimationParser::parseAnimation(tileset, animationPath, "IdleLeft", this);

	animations.emplace("IDLE_BOT", idleBot);
	animations.emplace("IDLE_TOP", idleTop);
	animations.emplace("IDLE_RIGHT", idleRight);
	animations.emplace("IDLE_LEFT", idleLeft);

	runBot = AnimationParser::parseAnimation(tileset, animationPath, "RunBot", this);
	runTop = AnimationParser::parseAnimation(tileset, animationPath, "RunTop", this);
	runRight = AnimationParser::parseAnimation(tileset, animationPath, "RunRight", this);
	runLeft = AnimationParser::parseAnimation(tileset, animationPath, "RunLeft", this);

	animations.emplace("RUN_BOT", runBot);
	animations.emplace("RUN_TOP", runTop);
	animations.emplace("RUN_RIGHT", runRight);
	animations.emplace("RUN_LEFT", runLeft);

	attackRight1 = AnimationParser::parseAnimation(tileset, animationPath, "AttackRight1", this, 10*Game::getGame()->getScale());
	attackRight2 = AnimationParser::parseAnimation(tileset, animationPath, "AttackRight2", this, 10 * Game::getGame()->getScale());
	attackRight3 = AnimationParser::parseAnimation(tileset, animationPath, "AttackRight3", this, 10 * Game::getGame()->getScale());

	animations.emplace("ATTACK1_RIGHT", attackRight1);
	animations.emplace("ATTACK2_RIGHT", attackRight2);
	animations.emplace("ATTACK3_RIGHT", attackRight3);

	attackLeft1 = AnimationParser::parseAnimation(tileset, animationPath, "AttackLeft1", this, -10 * Game::getGame()->getScale());
	attackLeft2 = AnimationParser::parseAnimation(tileset, animationPath, "AttackLeft2", this, -10 * Game::getGame()->getScale());
	attackLeft3 = AnimationParser::parseAnimation(tileset, animationPath, "AttackLeft3", this, -10 * Game::getGame()->getScale());

	animations.emplace("ATTACK1_LEFT", attackLeft1);
	animations.emplace("ATTACK2_LEFT", attackLeft2);
	animations.emplace("ATTACK3_LEFT", attackLeft3);

	attackTopLeft1 = AnimationParser::parseAnimation(tileset, animationPath, "AttackTopLeft1", this,0, -10 * Game::getGame()->getScale());
	attackTopLeft2  = AnimationParser::parseAnimation(tileset, animationPath, "AttackTopLeft2", this, 0, -10 * Game::getGame()->getScale());
	attackTopLeft3 = AnimationParser::parseAnimation(tileset, animationPath, "AttackTopLeft3", this, 0, -10 * Game::getGame()->getScale());

	animations.emplace("ATTACK1_TOPLEFT", attackTopLeft1);
	animations.emplace("ATTACK2_TOPLEFT", attackTopLeft2);
	animations.emplace("ATTACK3_TOPLEFT", attackTopLeft3);

	attackTopRight1  = AnimationParser::parseAnimation(tileset, animationPath, "AttackTopRight1", this, 0, -10 * Game::getGame()->getScale());
	attackTopRight2 = AnimationParser::parseAnimation(tileset, animationPath, "AttackTopRight2", this, 0, -10 * Game::getGame()->getScale());
	attackTopRight3 = AnimationParser::parseAnimation(tileset, animationPath, "AttackTopRight3", this, 0, -10 * Game::getGame()->getScale());

	animations.emplace("ATTACK1_TOPRIGHT", attackTopRight1);
	animations.emplace("ATTACK2_TOPRIGHT", attackTopRight2);
	animations.emplace("ATTACK3_TOPRIGHT", attackTopRight3);

	attackBotRight1 = AnimationParser::parseAnimation(tileset, animationPath, "AttackBotRight1", this);
	attackBotRight2 = AnimationParser::parseAnimation(tileset, animationPath, "AttackBotRight2", this);
	attackBotRight3 = AnimationParser::parseAnimation(tileset, animationPath, "AttackBotRight3", this);

	animations.emplace("ATTACK1_BOTRIGHT", attackBotRight1);
	animations.emplace("ATTACK2_BOTRIGHT", attackBotRight2);
	animations.emplace("ATTACK3_BOTRIGHT", attackBotRight3);

	attackBotLeft1 = AnimationParser::parseAnimation(tileset, animationPath, "AttackBotLeft1", this, 0);
	attackBotLeft2 = AnimationParser::parseAnimation(tileset, animationPath, "AttackBotLeft2", this, 0);
	attackBotLeft3 = AnimationParser::parseAnimation(tileset, animationPath, "AttackBotLeft3", this, 0);

	animations.emplace("ATTACK1_BOTLEFT", attackBotLeft1);
	animations.emplace("ATTACK2_BOTLEFT", attackBotLeft2);
	animations.emplace("ATTACK3_BOTLEFT", attackBotLeft3);
}

Animation* MainCharacter::getCurrentAnimation() {
	return animComp->getCurrentAnimation();
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
float MainCharacter::getMeleeDamage()
{
	return meleeDamage;
}
void MainCharacter::setMeleeDamage(float dmg)
{
	meleeDamage = dmg;
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
int MainCharacter::getCurrentRoomX()
{
	return currentRoomX;
}

int MainCharacter::getCurrentRoomY()
{
	return currentRoomY;
}

void MainCharacter::changeCurrentRoom(int x, int y)
{
	currentRoomX = x;
	currentRoomY = y;
}

int MainCharacter::getReloadTime()
{
	return reloadTime;
}

void MainCharacter::setReloadTime(int miliseconds)
{
	reloadTime = miliseconds;
}
