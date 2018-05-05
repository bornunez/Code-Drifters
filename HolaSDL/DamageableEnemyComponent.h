#pragma once
#include "UpdateComponent.h"
#include "MainCharacter.h"
#include "Timer.h"
class Enemy;

class DamageableEnemyComponent : virtual public UpdateComponent
{
public:
	DamageableEnemyComponent(Enemy* o, GameObject* mc);
	~DamageableEnemyComponent();
	void receiveMessage(Message* msg);
	void update();
	void receiveDamage(MCAttackType attackType, float damage);
private:
	float damage = 0;
	Timer * damageTimer;//Se usa para que la ulti no se ejecute al instante
	bool timerOn = false;
	Enemy* enemy;
	MainCharacter* mc;
};

