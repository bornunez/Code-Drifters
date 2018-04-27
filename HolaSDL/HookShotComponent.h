#pragma once
#include "UpdateComponent.h"
#include "Vector2D.h"
#include "Timer.h"
#include "HookCollisionComponent.h"
#include "PlayState.h"
#include "EnemyManager.h"
#include <iostream>
#include "EnemyGunner.h"
#include "CollisionHandler.h"
#include "MainCharacter.h"
#include <vector>
class MainCharacter;
class Hook;
class HookShotComponent :
	public UpdateComponent
{
private:
	float hookSpeed;
	Hook * hook;
	MainCharacter* mc;
	Enemy* enemyHooked=nullptr;
	vector<string> collisionsLayer;
public:
	void update();
	void updateHookPos();
	void receiveMessage(Message* msg);
	void shoot(Vector2D originPos, Vector2D hookDir);
	void extend();
	void contract();
	void moveEnemy();
	void moveMC();
	void stop();
	void updateHookAngle();
	HookShotComponent(MainCharacter* mc, Hook* h, float hookSpeed);
	virtual ~HookShotComponent();
};

