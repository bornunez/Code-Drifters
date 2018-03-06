#pragma once
#include "Enemy.h"
#include "Transform.h"
#include "MainCharacter.h"

Enemy::Enemy(Game* game, MainCharacter* mc, Transform t) : GameObject(game)
{
	mainCharacter = mc;
	transform.position.setX(t.position.getX());
	transform.position.setY(t.position.getY());
	transform.body.w = t.body.w;
	transform.body.h = t.body.h;

}
Enemy::Enemy(Game* game, MainCharacter* mc, int x, int y, int w, int h) : GameObject(game)
{
	mainCharacter = mc;
	transform.position.setX(x);
	transform.position.setY(y);
	transform.body.w = w;
	transform.body.h = h;
}

Enemy::~Enemy()
{
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
