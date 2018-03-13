#pragma once
#include "MainCharacter.h"
#include "Game.h"
#include "Camera.h"
#include "MCMovementComponent.h"
#include "PlayState.h"
#include "MCShotComponent.h"
#include "SkeletonRenderer.h"
#include "Texture.h"
#include "MCAnimationComponent.h"
#include "ResourceManager.h"
#include "MCMovementInput.h"
//Personaje principal




MainCharacter::MainCharacter(Texture * tex, int x, int y, int w, int h)
	: GameObject(tex, x, y, w, h)
{
	transform.position.setX(x);
	transform.position.setY(y);
	transform.body.w = w;
	transform.body.h = h;

	texture = Game::getGame()->getResourceManager()->getTexture(ProtaRun);	
	createRunAnimations();

	texture = Game::getGame()->getResourceManager()->getTexture(ProtaIdle);
	createIdleAnimation();
	setMaxVelocity(1);
	animComp = new MCAnimationComponent(this, animations);
	addComponent(animComp);
	addComponent(new MCMovementInput(this, SDL_SCANCODE_W, SDL_SCANCODE_D, SDL_SCANCODE_S, SDL_SCANCODE_A));
	addComponent(new MCMovementComponent(this));
	addComponent(new MCShotComponent(this));
	addComponent(new SkeletonRendered(this, playState->getCamera()));
	setCurrentBullets(4);
	setReloadTime(4);
	setMaxBullets(4);
	
	
}

MainCharacter::~MainCharacter()
{
}
//Animations
void MainCharacter::createRunAnimations()
{
	runLeft = new Animation(this, true, 0.05, 32, 32);
	runLeft->loadAnimation(0, 12, 2);
	for (int i = 0; i<runLeft->getNumberOfFrames(); i++) {
		SDL_Rect aux;
		aux.x = transform.position.getX();
		aux.y = transform.position.getY();
		aux.w = transform.body.w / 2;
		aux.h = transform.body.h;
		runLeft->getFrame(i)->setHurtbox(aux, 16);
	}

	runRight = new Animation(this, true, 0.05, 32, 32);
	runRight->loadAnimation(0, 12, 1);
	for (int i = 0; i<runRight->getNumberOfFrames(); i++) {
		SDL_Rect aux;
		aux.x = transform.position.getX();
		aux.y = transform.position.getY();
		aux.w = transform.body.w / 2;
		aux.h = transform.body.h;
		runRight->getFrame(i)->setHurtbox(aux, 16);
	}

	runBot = new Animation(this, true, 0.05, 32, 32);
	runBot->loadAnimation(0, 12, 0);
	for (int i = 0; i<runBot->getNumberOfFrames(); i++) {
		SDL_Rect aux;
		aux.x = transform.position.getX();
		aux.y = transform.position.getY();
		aux.w = transform.body.w / 2;
		aux.h = transform.body.h;
		runBot->getFrame(i)->setHurtbox(aux, 16);
	}

	runTop = new Animation(this, true, 0.05, 32, 32);
	runTop->loadAnimation(0, 12, 3);
	for (int i = 0; i<runTop->getNumberOfFrames(); i++) {
		SDL_Rect aux;
		aux.x = transform.position.getX();
		aux.y = transform.position.getY();
		aux.w = transform.body.w / 2;
		aux.h = transform.body.h;
		runTop->getFrame(i)->setHurtbox(aux, 16);
	}

	animations.emplace("RUN_LEFT", runLeft);
	animations.emplace("RUN_RIGHT", runRight);
	animations.emplace("RUN_BOT", runBot);
	animations.emplace("RUN_TOP", runTop);


}
void MainCharacter::createIdleAnimation()
{
	idleTop = new Animation(this, false, 5, 32, 32);
	idleTop->loadAnimation(1, 2, 0);

	idleBot = new Animation(this, false, 5, 32, 32);
	idleBot->loadAnimation(0, 1, 0);

	idleRight = new Animation(this, false, 5, 32, 32);
	idleRight->loadAnimation(2, 3, 0);

	idleLeft = new Animation(this, false, 5, 32, 32);
	idleLeft->loadAnimation(3, 4, 0);

	animations.emplace("IDLE_LEFT", idleLeft);
	animations.emplace("IDLE_RIGHT", idleRight);
	animations.emplace("IDLE_BOT", idleBot);
	animations.emplace("IDLE_TOP", idleTop);
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
