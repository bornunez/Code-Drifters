#pragma once
#include "Enemy.h"
#include "Game.h"
#include "Camera.h"
#include "Transform.h"
#include "MainCharacter.h"
#include "ChaseComponent.h"
#include "PlayState.h"

Enemy::Enemy(PlayState* playState, Game* game, MainCharacter* mc, Transform t) : PlayStateObject(playState, game)
{
	this->mainCharacter = mc;
	this->playState = playState;

	transform.position.setX(t.position.getX());
	transform.position.setY(t.position.getY());
	transform.body.w = t.body.w;
	transform.body.h = t.body.h;

	this->addComponent(new ChaseComponent(this, mainCharacter, 0.1));
}
Enemy::Enemy(PlayState* playState, Game* game, MainCharacter* mc, int x, int y, int w, int h) : PlayStateObject(playState, game)
{
	mainCharacter = mc;
	this->playState = playState;

	transform.position.setX(x);
	transform.position.setY(y);
	transform.body.w = w;
	transform.body.h = h;

	this->addComponent(new ChaseComponent(this, mainCharacter, 0.1));
}

Enemy::~Enemy()
{
}

void Enemy::render() {
	float auxX = transform.position.getX() - playState->getCamera()->getTransform()->position.getX();
	float auxY = transform.position.getY() - playState->getCamera()->getTransform()->position.getY();
	SDL_Rect rect RECT(auxX, auxY, transform.body.w, transform.body.h);
	SDL_SetRenderDrawColor(game->getRenderer(), COLOR(0xfff00fff));
	SDL_RenderFillRect(game->getRenderer(), &rect);
	SDL_SetRenderDrawColor(game->getRenderer(), COLOR(0x000ff0ff));
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
