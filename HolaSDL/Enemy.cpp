#pragma once
#include "Enemy.h"
#include "Game.h"
#include "Camera.h"
#include "Transform.h"
#include "MainCharacter.h"
#include "ChaseComponent.h"
#include "PlayState.h"

Enemy::Enemy(PlayState* playState, Game* game, MainCharacter* mc, Transform t) : PlayStateObject(playState)
{
	this->mainCharacter = mc;
	this->playState = playState;

	transform.position.setX(t.position.getX());
	transform.position.setY(t.position.getY());
	transform.body.w = t.body.w;
	transform.body.h = t.body.h;

}
Enemy::Enemy(PlayState* playState, Game* game, MainCharacter* mc, int x, int y, int w, int h) : PlayStateObject(playState)
{
	mainCharacter = mc;
	this->playState = playState;

	transform.position.setX(x);
	transform.position.setY(y);
	transform.body.w = w;
	transform.body.h = h;
}

Enemy::~Enemy()
{
}

void Enemy::render() {}

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
