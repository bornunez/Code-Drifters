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
//Personaje principal




MainCharacter::MainCharacter(Texture * tex, int x, int y, int w, int h)
	: GameObject(tex, x, y, w, h)
{
	transform.position.setX(x);
	transform.position.setY(y);
	transform.body.w = w;
	transform.body.h = h;

	texture = Game::getGame()->getResourceManager()->getTexture(TestSpritesheet);
	transform.speed = 10;
	setMaxVelocity(0.5);
	createAnimations();
	animComp = new MCAnimationComponent(this, animations);
	addComponent(animComp);
	addComponent(new MCMovementComponent(this, SDL_SCANCODE_W, SDL_SCANCODE_D, SDL_SCANCODE_S, SDL_SCANCODE_A));
	addComponent(new BasicMovement(this, "Paredes"));
	addComponent(new MCShotComponent(this));
	//addComponent(new SkeletonRendered(this, playState->getCamera()));
	setCurrentBullets(4);
	setReloadTime(4);
	setMaxBullets(4);
	
	
}

MainCharacter::~MainCharacter()
{
}
//Animations
void MainCharacter::createAnimations()
{
	walkLeft = new Animation(this, true, 0.05, 108, 140);
	walkLeft->loadAnimation(0, 7, 1);
	for (int i = 0; i<walkLeft->getNumberOfFrames(); i++) {
		SDL_Rect aux;
		aux.x = transform.position.getX();
		aux.y = transform.position.getY();
		aux.w = transform.body.w-10;
		aux.h = transform.body.h-10;
		walkLeft->getFrame(i)->setHurtbox(aux,5,20);
	}
	SDL_Rect aux;
	aux.x = transform.position.getX();
	aux.y = transform.position.getY();
	aux.w = transform.body.w - 30;
	aux.h = transform.body.h - 30;
	walkLeft->getFrame(3)->setHitbox(aux, -40);

	walkRight = new Animation(this, true, 0.05, 108, 140);
	walkRight->loadAnimation(0, 7, 0);
	for (int i = 0; i<walkRight->getNumberOfFrames(); i++) {
		SDL_Rect aux;
		aux.x = transform.position.getX();
		aux.y = transform.position.getY();
		aux.w = transform.body.w;
		aux.h = transform.body.h;
		walkRight->getFrame(i)->setHurtbox(aux);
	}

	animations.emplace("WALK_LEFT", walkLeft);
	animations.emplace("WALK_RIGHT", walkRight);
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
