#pragma once
#include "Enemy.h"
#include "Game.h"
#include "Camera.h"
#include "Transform.h"
#include "MainCharacter.h"
#include "PlayState.h"
#include "GameObject.h"
#include "EnemyManager.h"
#include "Map.h"
#include "ItemManager.h"
#include "CoinManager.h"

#include"EnemyHUDComponent.h"

Enemy::Enemy(MainCharacter* mc) : GameObject()
{
	this->mainCharacter = mc;
	transform.position.set(10, 10);
	hud = new EnemyHUDComponent(this);
	this->addComponent(hud);
	//this->addComponent(new StunComponent(this));
	//this->addComponent(new ChaseComponent(this, mainCharacter, 0.1));
}

Enemy::~Enemy()
{
}

void Enemy::spawn(int x, int y, Spawner* spawner)
{
	//Lo spawneamos en la posicion que digan
	transform.position.setX(x); transform.position.setY(y);
	transform.body.x = x; transform.body.y = y;
	updatePreviousPosition();	
	updateBody();
	allUpdates();

	//Y ponemos sus valores por defecto
	EnemyParams params = EnemyManager::getInstance()->getParams(type);
	Attributes.maxLife = Attributes.life = params.life;
	transform.speed = params.speed;
	baseSpeed = params.speed;
	Attributes.meleeDmg = params.meleDmg; Attributes.rangedDmg = params.rangedDmg ;
	Attributes.minDrop = params.minDrop; Attributes.maxDrop = params.maxDrop; Attributes.healDrop = params.healDrop;
	Attributes.hookable = params.hookable;
	this->spawner = spawner;
	Attributes.stunned = false;
	setMovable(true);
	setDeath(false);
	Message msg(ENEMY_SPAWN);
	sendMessage(&msg);
}

void Enemy::render() {
	GameObject::render();
}

void Enemy::update()
{
	GameObject::update();
	//hud->update();
}

MainCharacter* Enemy::getMC() {
	return mainCharacter;
}






void Enemy::onDestroy() {
	//Si tenemos un spawner asignado, nos destruimos
	if(spawner != nullptr)
		spawner->setActive(false);
}

void Enemy::death()
{
	setMovable(false);
	setDeath(true);

	if (Random::randomInt(0, 100) < Attributes.healDrop) {
		ItemManager::getInstance()->AddItem(Enemies, centerPosition);
	}

	int maxCoins = Attributes.maxDrop; int minCoins = Attributes.minDrop;
	int drop = rand() % (maxCoins - minCoins + 1) + minCoins;
	CoinManager::getInstance()->Drop(drop,centerPosition.getX(), centerPosition.getY());

	Message msg(ENEMY_DEATH);
	sendMessage(&msg);
	mainCharacter->sendMessage(&msg);
}

