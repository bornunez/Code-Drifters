#pragma once
#include "Enemy.h"
#include "Game.h"
#include "Camera.h"
#include "Transform.h"
#include "MainCharacter.h"
#include "ChaseComponent.h"
#include "PlayState.h"
#include "EnemyManager.h"

Enemy::Enemy(PlayState* playState, MainCharacter* mc) : PlayStateObject(playState)
{
	this->mainCharacter = mc;
	//this->addComponent(new ChaseComponent(this, mainCharacter, 0.1));
}

Enemy::~Enemy()
{
}

void Enemy::spawn(int x, int y)
{
	//Lo spawneamos en la posicion que digan
	transform.position.setX(x); transform.position.setY(y);
	transform.body.x = x; transform.body.y = y;
	//Y ponemos sus valores por defecto
	EnemyParams params = EnemyManager::getInstance()->getParams(type);
	life = params.life; 
	speed = params.speed;
	meleeDmg = params.meleDmg; rangedDmg = params.rangedDmg ;
	minDrop = params.minDrop; maxDrop = params.maxDrop;

}

void Enemy::render() {
	float auxX = transform.position.getX() - playState->getCamera()->getTransform()->position.getX();
	float auxY = transform.position.getY() - playState->getCamera()->getTransform()->position.getY();
	SDL_Rect rect RECT(auxX, auxY, transform.body.w, transform.body.h);
	SDL_SetRenderDrawColor(game->getRenderer(), COLOR(0xfff00fff));
	SDL_RenderFillRect(game->getRenderer(), &rect);
	SDL_SetRenderDrawColor(game->getRenderer(), COLOR(0x000ff0ff));
}

void Enemy::update()
{
	PlayStateObject::update();
}

GameObject* Enemy::getMC() {
	return mainCharacter;
}


void Enemy::receiveDamage(int damage) {
	life -= damage;
	if (life <= 0) {
		onDestroy();
	}
}

void Enemy::onDestroy() {
	//droppear dinero etc
}
