#pragma once
#include "MainCharacter.h"
#include "Game.h"
#include "Camera.h"
#include "MCMovementComponent.h"
#include "PlayState.h"
#include "MCShotComponent.h"

//Personaje principal




MainCharacter::MainCharacter(PlayState * playState, Game * game, Texture * tex, int x, int y, int w, int h)
	: PlayStateObject(playState, game, tex, x, y, w, h)
{
	transform.position.setX(x);
	transform.position.setY(y);
	transform.body.w = w;
	transform.body.h = h;

	setMaxVelocity(0.5);
	addComponent(new MCMovementComponent(this, SDL_SCANCODE_W, SDL_SCANCODE_D, SDL_SCANCODE_S, SDL_SCANCODE_A));
	addComponent(new MCShotComponent(this));
	setCurrentBullets(4);
	setReloadTime(4000);
	setMaxBullets(4);
}

MainCharacter::~MainCharacter()
{
}
void MainCharacter::render() {
	float auxX = transform.position.getX() - getPlayState()->getCamera()->getTransform()->position.getX();
	float auxY = transform.position.getY() - getPlayState()->getCamera()->getTransform()->position.getY();
	SDL_Rect rect RECT(auxX, auxY, transform.body.w, transform.body.h);
	SDL_SetRenderDrawColor(game->getRenderer(), COLOR(0xff00ffff));
	SDL_RenderFillRect(game->getRenderer(), &rect);
	SDL_SetRenderDrawColor(game->getRenderer(), COLOR(0x000000ff));
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
