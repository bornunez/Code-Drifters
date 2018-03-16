#pragma once
#include "MainCharacter.h"
#include "Game.h"
#include "Camera.h"
#include "MCMovementComponent.h"
#include "PlayState.h"
#include "BasicMovement.h"
#include "MCShotComponent.h"
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

	string animationPath = "../Animations/Protagonist/tileset/ProtaAnimation.tmx";
	idleBot = AnimationParser::parseAnimation(animationPath, "IdleBot", this);
	idleTop = AnimationParser::parseAnimation(animationPath, "IdleTop", this);
	idleRight = AnimationParser::parseAnimation(animationPath, "IdleRight", this);
	idleLeft = AnimationParser::parseAnimation(animationPath, "IdleLeft", this);

	animations.emplace("IDLE_BOT", idleBot);
	animations.emplace("IDLE_TOP", idleTop);
	animations.emplace("IDLE_RIGHT", idleRight);
	animations.emplace("IDLE_LEFT", idleLeft);

	runBot = AnimationParser::parseAnimation(animationPath, "RunBot", this);
	runTop = AnimationParser::parseAnimation(animationPath, "RunTop", this);
	runRight = AnimationParser::parseAnimation(animationPath, "RunRight", this);
	runLeft = AnimationParser::parseAnimation(animationPath, "RunLeft", this);

	animations.emplace("RUN_BOT", runBot);
	animations.emplace("RUN_TOP", runTop);
	animations.emplace("RUN_RIGHT", runRight);
	animations.emplace("RUN_LEFT", runLeft);

	attackRight1 = AnimationParser::parseAnimation(animationPath, "AttackRight1", this, 10*Game::getGame()->getScale());
	attackRight2 = AnimationParser::parseAnimation(animationPath, "AttackRight2", this, 10 * Game::getGame()->getScale());
	attackRight3 = AnimationParser::parseAnimation(animationPath, "AttackRight3", this, 10 * Game::getGame()->getScale());

	animations.emplace("ATTACK1_RIGHT", attackRight1);
	animations.emplace("ATTACK2_RIGHT", attackRight2);
	animations.emplace("ATTACK3_RIGHT", attackRight3);

	attackLeft1 = AnimationParser::parseAnimation(animationPath, "AttackLeft1", this, -10 * Game::getGame()->getScale());
	attackLeft2 = AnimationParser::parseAnimation(animationPath, "AttackLeft2", this, -10 * Game::getGame()->getScale());
	attackLeft3 = AnimationParser::parseAnimation(animationPath, "AttackLeft3", this, -10 * Game::getGame()->getScale());

	animations.emplace("ATTACK1_LEFT", attackLeft1);
	animations.emplace("ATTACK2_LEFT", attackLeft2);
	animations.emplace("ATTACK3_LEFT", attackLeft3);

	attackTopLeft1 = AnimationParser::parseAnimation(animationPath, "AttackTopLeft1", this,0, -10 * Game::getGame()->getScale());
	attackTopLeft2  = AnimationParser::parseAnimation(animationPath, "AttackTopLeft2", this, 0, -10 * Game::getGame()->getScale());
	attackTopLeft3 = AnimationParser::parseAnimation(animationPath, "AttackTopLeft3", this, 0, -10 * Game::getGame()->getScale());

	animations.emplace("ATTACK1_TOPLEFT", attackTopLeft1);
	animations.emplace("ATTACK2_TOPLEFT", attackTopLeft2);
	animations.emplace("ATTACK3_TOPLEFT", attackTopLeft3);

	attackTopRight1  = AnimationParser::parseAnimation(animationPath, "AttackTopRight1", this, 0, -10 * Game::getGame()->getScale());
	attackTopRight2 = AnimationParser::parseAnimation(animationPath, "AttackTopRight2", this, 0, -10 * Game::getGame()->getScale());
	attackTopRight3 = AnimationParser::parseAnimation(animationPath, "AttackTopRight3", this, 0, -10 * Game::getGame()->getScale());

	animations.emplace("ATTACK1_TOPRIGHT", attackTopRight1);
	animations.emplace("ATTACK2_TOPRIGHT", attackTopRight2);
	animations.emplace("ATTACK3_TOPRIGHT", attackTopRight3);
}
//Animations
//void MainCharacter::createRunAnimations()
//{
//	runLeft = new Animation(this, true, 0.05, 32, 32);
//	runLeft->loadAnimation(0, 12, 3);
//	for (int i = 0; i<runLeft->getNumberOfFrames(); i++) {
//		SDL_Rect aux;
//		aux.x = transform.position.getX();
//		aux.y = transform.position.getY();
//		aux.w = transform.body.w / 2;
//		aux.h = transform.body.h;
//		runLeft->getFrame(i)->addHurtbox(aux, transform.body.w / 4);
//	}
//
//	runRight = new Animation(this, true, 0.05, 32, 32);
//	runRight->loadAnimation(0, 12, 2);
//	for (int i = 0; i<runRight->getNumberOfFrames(); i++) {
//		SDL_Rect aux;
//		aux.x = transform.position.getX();
//		aux.y = transform.position.getY();
//		aux.w = transform.body.w / 2;
//		aux.h = transform.body.h;
//		runRight->getFrame(i)->addHurtbox(aux, transform.body.w / 4);
//	}
//
//	runBot = new Animation(this, true, 0.05, 32, 32);
//	runBot->loadAnimation(0, 12, 1);
//	for (int i = 0; i<runBot->getNumberOfFrames(); i++) {
//		SDL_Rect aux;
//		aux.x = transform.position.getX();
//		aux.y = transform.position.getY();
//		aux.w = transform.body.w / 2;
//		aux.h = transform.body.h;
//		runBot->getFrame(i)->addHurtbox(aux, transform.body.w / 4);
//	}
//
//	runTop = new Animation(this, true, 0.05, 32, 32);
//	runTop->loadAnimation(0, 12, 4);
//	for (int i = 0; i<runTop->getNumberOfFrames(); i++) {
//		SDL_Rect aux;
//		aux.x = transform.position.getX();
//		aux.y = transform.position.getY();
//		aux.w = transform.body.w / 2;
//		aux.h = transform.body.h;
//		runTop->getFrame(i)->addHurtbox(aux, transform.body.w / 4);
//	}
//
//	animations.emplace("RUN_LEFT", runLeft);
//	animations.emplace("RUN_RIGHT", runRight);
//	animations.emplace("RUN_BOT", runBot);
//	animations.emplace("RUN_TOP", runTop);
//
//
//}
//void MainCharacter::createIdleAnimation()
//{
//	SDL_Rect idleHurtBox;
//	idleHurtBox.x = transform.position.getX();
//	idleHurtBox.y = transform.position.getY();
//	idleHurtBox.w = transform.body.w / 2;
//	idleHurtBox.h = transform.body.h;
//
//	idleTop = new Animation(this, false, 5, 32, 32);
//	idleTop->loadAnimation(1, 2, 0);
//	idleTop->getFrame(0)->addHurtbox(idleHurtBox, transform.body.w / 4);
//
//	idleBot = new Animation(this, false, 5, 32, 32);
//	idleBot->loadAnimation(0, 1, 0);
//	idleBot->getFrame(0)->addHurtbox(idleHurtBox, transform.body.w / 4);	
//
//	idleRight = new Animation(this, false, 5, 32, 32);
//	idleRight->loadAnimation(2, 3, 0);
//	idleRight->getFrame(0)->addHurtbox(idleHurtBox, transform.body.w / 4);
//
//	idleLeft = new Animation(this, false, 5, 32, 32);
//	idleLeft->loadAnimation(3, 4, 0);
//	idleLeft->getFrame(0)->addHurtbox(idleHurtBox, transform.body.w / 4);
//
//	animations.emplace("IDLE_LEFT", idleLeft);
//	animations.emplace("IDLE_RIGHT", idleRight);
//	animations.emplace("IDLE_BOT", idleBot);
//	animations.emplace("IDLE_TOP", idleTop);
//}
//void MainCharacter::createLeftAttackAnimation()
//{
//	//ATTACKLEFT 1
//	attackLeft1 = new Animation(this, true, 0.05, 54, 40);
//	attackLeft1->loadAnimation(0, 8, 7,-transform.body.w/2);
//	//Creación de hurtboxes
//	for (int i = 0; i<attackLeft1->getNumberOfFrames(); i++) {
//		SDL_Rect aux;
//		aux.x = transform.position.getX();
//		aux.y = transform.position.getY();
//		aux.w = transform.body.w / 2;
//		aux.h = transform.body.h/1.2;
//		attackLeft1->getFrame(i)->addHurtbox(aux, transform.body.w /2, transform.body.h/7);
//	}
//	//Frame 1 Hitbox0
//	SDL_Rect aux;
//	aux.x = transform.position.getX();
//	aux.y = transform.position.getY();
//	aux.w = transform.body.w / 2;
//	aux.h = transform.body.h/3;
//	attackLeft1->getFrame(1)->addHitbox(aux,transform.body.w/2,transform.body.h/1.5);
//	//Frame 1 Hitbox1
//	aux.w = transform.body.w/1.2;
//	aux.h = transform.body.h / 1.1;
//	attackLeft1->getFrame(1)->addHitbox(aux,-transform.body.w/3,transform.body.h/10);
//	//Frame 2 Hitbox0
//	aux.w = transform.body.w/1.5;
//	aux.h = transform.body.h / 2.75;
//	attackLeft1->getFrame(2)->addHitbox(aux, transform.body.w/20, transform.body.h / 1.5);
//	//Frame 2 Hitbox1
//	aux.w = transform.body.w/2;
//	aux.h = transform.body.h / 5.75;
//	attackLeft1->getFrame(2)->addHitbox(aux, -transform.body.w / 3, transform.body.h / 1.2);
//	
//
//	//ATTACKLEFT 2
//	attackLeft2 = new Animation(this, true, 0.05, 54, 40);
//	attackLeft2->loadAnimation(0, 11, 8, -transform.body.w / 2);
//	//Creación de hurtboxes
//	for (int i = 0; i<attackLeft2->getNumberOfFrames(); i++) {
//		SDL_Rect aux;
//		aux.x = transform.position.getX();
//		aux.y = transform.position.getY();
//		aux.w = transform.body.w / 2;
//		aux.h = transform.body.h / 1.2;
//		attackLeft2->getFrame(i)->addHurtbox(aux, transform.body.w / 2, transform.body.h / 7);
//	}
//	//Frame 1 Hitbox0
//	aux.x = transform.position.getX();
//	aux.y = transform.position.getY();
//	aux.w = transform.body.w / 2;
//	aux.h = transform.body.h / 1.1;
//	attackLeft2->getFrame(1)->addHitbox(aux);
//	//Frame 1 Hitbox1
//	aux.w = transform.body.w / 4;
//	aux.h = transform.body.h / 1.4;
//	attackLeft2->getFrame(1)->addHitbox(aux, -transform.body.w / 4, transform.body.h / 10);
//	//Frame 1 Hitbox2
//	aux.w = transform.body.w / 10;
//	aux.h = transform.body.h / 2;
//	attackLeft2->getFrame(1)->addHitbox(aux, -transform.body.w / 3, transform.body.h / 4);
//	//Frame 2 Hitbox0
//	aux.w = transform.body.w*1.2;
//	aux.h = transform.body.h / 3;
//	attackLeft2->getFrame(2)->addHitbox(aux, -transform.body.w / 4, transform.body.h / 20);
//	//Frame 3 Hitbox0
//	aux.w = transform.body.w*1.2;
//	aux.h = transform.body.h / 7;
//	attackLeft2->getFrame(3)->addHitbox(aux, -transform.body.w / 5, transform.body.h / 20);
//
//
//
//	//ATTACKLEFT 3
//	attackLeft3 = new Animation(this, true, 0.05, 54, 40);
//	attackLeft3->loadAnimation(0, 13, 9, -transform.body.w / 2);
//	//Creación de hurtboxes
//	for (int i = 0; i<attackLeft3->getNumberOfFrames(); i++) {
//		SDL_Rect aux;
//		aux.x = transform.position.getX();
//		aux.y = transform.position.getY();
//		aux.w = transform.body.w / 2;
//		aux.h = transform.body.h / 1.2;
//		attackLeft3->getFrame(i)->addHurtbox(aux, transform.body.w / 3, transform.body.h / 7);
//	}
//	//Frame 1 Hitbox0
//	aux.x = transform.position.getX();
//	aux.y = transform.position.getY();
//	aux.w = transform.body.w / 2;
//	aux.h = transform.body.h / 1;
//	attackLeft3->getFrame(1)->addHitbox(aux,transform.body.w/10);
//	//Frame 1 Hitbox1
//	aux.w = transform.body.w / 4;
//	aux.h = transform.body.h / 1.2;
//	attackLeft3->getFrame(1)->addHitbox(aux, -transform.body.w / 6, transform.body.h / 9);
//	//Frame 1 Hitbox2
//	aux.w = transform.body.w / 10;
//	aux.h = transform.body.h / 2;
//	attackLeft3->getFrame(1)->addHitbox(aux, -transform.body.w / 4, transform.body.h / 3);
//	//Frame 2 Hitbox0
//	aux.w = transform.body.w/1.5;
//	aux.h = transform.body.h / 4;
//	attackLeft3->getFrame(2)->addHitbox(aux, 0, transform.body.h / 1.3);
//
//
//	animations.emplace("ATTACK1_LEFT", attackLeft1);
//	animations.emplace("ATTACK2_LEFT", attackLeft2);
//	animations.emplace("ATTACK3_LEFT", attackLeft3);
//}
//void MainCharacter::createRightAttackAnimation()
//{
//	//ATTACKRIGHT 1
//	attackRight1 = new Animation(this, true, 0.05, 54, 40);
//	attackRight1->loadAnimation(0, 8, 4);
//	//Creación de hurtboxes
//	for (int i = 0; i<attackRight1->getNumberOfFrames(); i++) {
//		SDL_Rect aux;
//		aux.x = transform.position.getX();
//		aux.y = transform.position.getY();
//		aux.w = transform.body.w / 2;
//		aux.h = transform.body.h / 1.2;
//		attackRight1->getFrame(i)->addHurtbox(aux, transform.body.w / 4, transform.body.h / 7);
//	}
//	//Frame 1 Hitbox0
//	SDL_Rect aux;
//	aux.x = transform.position.getX();
//	aux.y = transform.position.getY();
//	aux.w = transform.body.w / 2;
//	aux.h = transform.body.h / 3;
//	attackRight1->getFrame(1)->addHitbox(aux, transform.body.w/4 , transform.body.h / 1.5);
//	//Frame 1 Hitbox1
//	aux.w = transform.body.w / 1.2;
//	aux.h = transform.body.h / 1.1;
//	attackRight1->getFrame(1)->addHitbox(aux, transform.body.w / 1.5, transform.body.h / 10);
//	//Frame 2 Hitbox0
//	aux.w = transform.body.w / 1.2;
//	aux.h = transform.body.h / 2.75;
//	attackRight1->getFrame(2)->addHitbox(aux, transform.body.w / 2, transform.body.h / 1.5);
//
//	//ATTACKRIGHT 2
//	attackRight2 = new Animation(this, true, 0.05, 54, 40);
//	attackRight2->loadAnimation(0, 11, 5);
//	//Creación de hurtboxes
//	for (int i = 0; i<attackRight2->getNumberOfFrames(); i++) {
//		SDL_Rect aux;
//		aux.x = transform.position.getX();
//		aux.y = transform.position.getY();
//		aux.w = transform.body.w / 2;
//		aux.h = transform.body.h / 1.2;
//		attackRight2->getFrame(i)->addHurtbox(aux, transform.body.w / 4, transform.body.h / 7);
//	}
//	//Frame 1 Hitbox0
//	aux.x = transform.position.getX();
//	aux.y = transform.position.getY();
//	aux.w = transform.body.w / 2;
//	aux.h = transform.body.h / 1.1;
//	attackRight2->getFrame(1)->addHitbox(aux, transform.body.w/2);
//	//Frame 1 Hitbox1
//	aux.w = transform.body.w / 4;
//	aux.h = transform.body.h / 1.4;
//	attackRight2->getFrame(1)->addHitbox(aux, transform.body.w, transform.body.h / 10);
//	//Frame 1 Hitbox2
//	aux.w = transform.body.w / 4.5;
//	aux.h = transform.body.h / 1.7;
//	attackRight2->getFrame(1)->addHitbox(aux, transform.body.w*1.3, transform.body.h / 4.5);
//	//Frame 2 Hitbox0
//	aux.w = transform.body.w*1.2;
//	aux.h = transform.body.h / 3;
//	attackRight2->getFrame(2)->addHitbox(aux, transform.body.w/4, transform.body.h / 20);
//	//Frame 3 Hitbox0
//	aux.w = transform.body.w*1.2;
//	aux.h = transform.body.h / 7;
//	attackRight2->getFrame(3)->addHitbox(aux, transform.body.w / 4, transform.body.h / 20);
//
//
//
//	//ATTACKRIGHT 3
//	attackRight3 = new Animation(this, true, 0.05, 54, 40);
//	attackRight3->loadAnimation(0, 13, 6);
//	//Creación de hurtboxes
//	for (int i = 0; i<attackRight3->getNumberOfFrames(); i++) {
//		SDL_Rect aux;
//		aux.x = transform.position.getX();
//		aux.y = transform.position.getY();
//		aux.w = transform.body.w / 1.5;
//		aux.h = transform.body.h / 1.3;
//		attackRight3->getFrame(i)->addHurtbox(aux, transform.body.w / 4, transform.body.h / 6);
//	}
//	//Frame 1 Hitbox0
//	aux.x = transform.position.getX();
//	aux.y = transform.position.getY();
//	aux.w = transform.body.w / 2;
//	aux.h = transform.body.h / 1;
//	attackRight3->getFrame(1)->addHitbox(aux, transform.body.w/2);
//	//Frame 1 Hitbox1
//	aux.w = transform.body.w / 4;
//	aux.h = transform.body.h / 1.2;
//	attackRight3->getFrame(1)->addHitbox(aux, transform.body.w , transform.body.h / 9);
//	////Frame 1 Hitbox2
//	aux.w = transform.body.w / 7;
//	aux.h = transform.body.h / 1.8;
//	attackRight3->getFrame(1)->addHitbox(aux, transform.body.w*1.25, transform.body.h / 4);
//	//Frame 2 Hitbox0
//	aux.w = transform.body.w / 1.5;
//	aux.h = transform.body.h / 4;
//	attackRight3->getFrame(2)->addHitbox(aux, transform.body.w/1.5, transform.body.h / 1.3);
//
//	animations.emplace("ATTACK1_RIGHT", attackRight1);
//	animations.emplace("ATTACK2_RIGHT", attackRight2);
//	animations.emplace("ATTACK3_RIGHT", attackRight3);
//}
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
