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
//Personaje principal




MainCharacter::MainCharacter(Texture * tex, int x, int y, int w, int h)
	: GameObject(tex, x, y, w, h)
{
	transform.position.setX(x);
	transform.position.setY(y);
	transform.body.w = w;
	transform.body.h = h;
	texture = GameManager::getInstance()->getResourceManager()->getTexture(ProtaAnimation);
	createRunAnimations();
	createIdleAnimation();
	createLeftAttackAnimation();

	transform.speed = 500;
	//setMaxVelocity(0.5);

	
	addComponent(new MCMovementInput(this, SDL_SCANCODE_W, SDL_SCANCODE_D, SDL_SCANCODE_S, SDL_SCANCODE_A));
	addComponent(new MCMovementComponent(this));
	addComponent(new BasicMovement(this, "Paredes"));
	addComponent(new MCShotComponent(this));
	addComponent(new SkeletonRendered(this));
	animComp = new MCAnimationComponent(this, animations);
	addComponent(animComp);
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
	runLeft->loadAnimation(0, 12, 3);
	for (int i = 0; i<runLeft->getNumberOfFrames(); i++) {
		SDL_Rect aux;
		aux.x = transform.position.getX();
		aux.y = transform.position.getY();
		aux.w = transform.body.w / 2;
		aux.h = transform.body.h;
		runLeft->getFrame(i)->addHurtbox(aux, transform.body.w / 4);
	}

	runRight = new Animation(this, true, 0.05, 32, 32);
	runRight->loadAnimation(0, 12, 2);
	for (int i = 0; i<runRight->getNumberOfFrames(); i++) {
		SDL_Rect aux;
		aux.x = transform.position.getX();
		aux.y = transform.position.getY();
		aux.w = transform.body.w / 2;
		aux.h = transform.body.h;
		runRight->getFrame(i)->addHurtbox(aux, transform.body.w / 4);
	}

	runBot = new Animation(this, true, 0.05, 32, 32);
	runBot->loadAnimation(0, 12, 1);
	for (int i = 0; i<runBot->getNumberOfFrames(); i++) {
		SDL_Rect aux;
		aux.x = transform.position.getX();
		aux.y = transform.position.getY();
		aux.w = transform.body.w / 2;
		aux.h = transform.body.h;
		runBot->getFrame(i)->addHurtbox(aux, transform.body.w / 4);
	}

	runTop = new Animation(this, true, 0.05, 32, 32);
	runTop->loadAnimation(0, 12, 4);
	for (int i = 0; i<runTop->getNumberOfFrames(); i++) {
		SDL_Rect aux;
		aux.x = transform.position.getX();
		aux.y = transform.position.getY();
		aux.w = transform.body.w / 2;
		aux.h = transform.body.h;
		runTop->getFrame(i)->addHurtbox(aux, transform.body.w / 4);
	}

	animations.emplace("RUN_LEFT", runLeft);
	animations.emplace("RUN_RIGHT", runRight);
	animations.emplace("RUN_BOT", runBot);
	animations.emplace("RUN_TOP", runTop);


}
void MainCharacter::createIdleAnimation()
{
	SDL_Rect idleHurtBox;
	idleHurtBox.x = transform.position.getX();
	idleHurtBox.y = transform.position.getY();
	idleHurtBox.w = transform.body.w / 2;
	idleHurtBox.h = transform.body.h;

	idleTop = new Animation(this, false, 5, 32, 32);
	idleTop->loadAnimation(1, 2, 0);
	idleTop->getFrame(0)->addHurtbox(idleHurtBox, transform.body.w / 4);

	idleBot = new Animation(this, false, 5, 32, 32);
	idleBot->loadAnimation(0, 1, 0);
	idleBot->getFrame(0)->addHurtbox(idleHurtBox, transform.body.w / 4);	

	idleRight = new Animation(this, false, 5, 32, 32);
	idleRight->loadAnimation(2, 3, 0);
	idleRight->getFrame(0)->addHurtbox(idleHurtBox, transform.body.w / 4);

	idleLeft = new Animation(this, false, 5, 32, 32);
	idleLeft->loadAnimation(3, 4, 0);
	idleLeft->getFrame(0)->addHurtbox(idleHurtBox, transform.body.w / 4);

	animations.emplace("IDLE_LEFT", idleLeft);
	animations.emplace("IDLE_RIGHT", idleRight);
	animations.emplace("IDLE_BOT", idleBot);
	animations.emplace("IDLE_TOP", idleTop);
}
void MainCharacter::createLeftAttackAnimation()
{
	//ATTACKLEFT 1
	attackLeft1 = new Animation(this, true, 0.05, 54, 40);
	attackLeft1->loadAnimation(0, 8, 7,-transform.body.w/2);
	//Creación de hurtboxes
	for (int i = 0; i<attackLeft1->getNumberOfFrames(); i++) {
		SDL_Rect aux;
		aux.x = transform.position.getX();
		aux.y = transform.position.getY();
		aux.w = transform.body.w / 2;
		aux.h = transform.body.h/1.2;
		attackLeft1->getFrame(i)->addHurtbox(aux, transform.body.w / 2, transform.body.h/7);
	}
	//Frame 1 Hitbox0
	SDL_Rect aux;
	aux.x = transform.position.getX();
	aux.y = transform.position.getY();
	aux.w = transform.body.w / 2;
	aux.h = transform.body.h/3;
	attackLeft1->getFrame(1)->addHitbox(aux,transform.body.w/2,transform.body.h/1.5);
	//Frame 1 Hitbox1
	aux.w = transform.body.w/1.2;
	aux.h = transform.body.h / 1.1;
	attackLeft1->getFrame(1)->addHitbox(aux,-transform.body.w/3,transform.body.h/10);
	//Frame 2 Hitbox0
	aux.w = transform.body.w/1.5;
	aux.h = transform.body.h / 2.75;
	attackLeft1->getFrame(2)->addHitbox(aux, transform.body.w/20, transform.body.h / 1.5);
	//Frame 2 Hitbox1
	aux.w = transform.body.w/2;
	aux.h = transform.body.h / 5.75;
	attackLeft1->getFrame(2)->addHitbox(aux, -transform.body.w / 3, transform.body.h / 1.2);
	

	//ATTACKLEFT 2
	attackLeft2 = new Animation(this, true, 0.05, 54, 40);
	attackLeft2->loadAnimation(0, 11, 8, -transform.body.w / 2);
	//Creación de hurtboxes
	for (int i = 0; i<attackLeft2->getNumberOfFrames(); i++) {
		SDL_Rect aux;
		aux.x = transform.position.getX();
		aux.y = transform.position.getY();
		aux.w = transform.body.w / 2;
		aux.h = transform.body.h / 1.2;
		attackLeft2->getFrame(i)->addHurtbox(aux, transform.body.w / 2, transform.body.h / 7);
	}
	//Frame 1 Hitbox0
	aux.x = transform.position.getX();
	aux.y = transform.position.getY();
	aux.w = transform.body.w / 2;
	aux.h = transform.body.h / 1.1;
	attackLeft2->getFrame(1)->addHitbox(aux);
	//Frame 1 Hitbox1
	aux.w = transform.body.w / 4;
	aux.h = transform.body.h / 1.4;
	attackLeft2->getFrame(1)->addHitbox(aux, -transform.body.w / 4, transform.body.h / 10);
	//Frame 1 Hitbox2
	aux.w = transform.body.w / 10;
	aux.h = transform.body.h / 2;
	attackLeft2->getFrame(1)->addHitbox(aux, -transform.body.w / 3, transform.body.h / 4);
	//Frame 2 Hitbox0
	aux.w = transform.body.w*1.2;
	aux.h = transform.body.h / 3;
	attackLeft2->getFrame(2)->addHitbox(aux, -transform.body.w / 4, transform.body.h / 20);
	//Frame 3 Hitbox0
	aux.w = transform.body.w*1.2;
	aux.h = transform.body.h / 7;
	attackLeft2->getFrame(3)->addHitbox(aux, -transform.body.w / 5, transform.body.h / 20);



	//ATTACKLEFT 3
	attackLeft3 = new Animation(this, true, 3, 54, 40);
	attackLeft3->loadAnimation(0, 13, 9, -transform.body.w / 2);
	//Creación de hurtboxes
	for (int i = 0; i<attackLeft3->getNumberOfFrames(); i++) {
		SDL_Rect aux;
		aux.x = transform.position.getX();
		aux.y = transform.position.getY();
		aux.w = transform.body.w / 2;
		aux.h = transform.body.h / 1.2;
		attackLeft3->getFrame(i)->addHurtbox(aux, transform.body.w / 3, transform.body.h / 7);
	}
	//Frame 1 Hitbox0
	aux.x = transform.position.getX();
	aux.y = transform.position.getY();
	aux.w = transform.body.w / 2;
	aux.h = transform.body.h / 1;
	attackLeft3->getFrame(1)->addHitbox(aux,transform.body.w/10);
	//Frame 1 Hitbox1
	aux.w = transform.body.w / 4;
	aux.h = transform.body.h / 1.2;
	attackLeft3->getFrame(1)->addHitbox(aux, -transform.body.w / 6, transform.body.h / 9);
	//Frame 1 Hitbox2
	aux.w = transform.body.w / 10;
	aux.h = transform.body.h / 2;
	attackLeft3->getFrame(1)->addHitbox(aux, -transform.body.w / 4, transform.body.h / 3);
	//Frame 2 Hitbox0
	aux.w = transform.body.w/1.5;
	aux.h = transform.body.h / 4;
	attackLeft3->getFrame(2)->addHitbox(aux, 0, transform.body.h / 1.3);


	animations.emplace("ATTACK1_LEFT", attackLeft1);
	animations.emplace("ATTACK2_LEFT", attackLeft2);
	animations.emplace("ATTACK3_LEFT", attackLeft3);
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
int MainCharacter::getReloadTime()
{
	return reloadTime;
}

void MainCharacter::setReloadTime(int miliseconds)
{
	reloadTime = miliseconds;
}
