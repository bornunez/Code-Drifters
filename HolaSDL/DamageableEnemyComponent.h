#pragma once
#include "UpdateComponent.h"
#include "MainCharacter.h"
#include "Timer.h"
class Enemy;

class DamageableEnemyComponent : virtual public UpdateComponent
{
public:
	DamageableEnemyComponent(Enemy* o, MainCharacter* mc, float invincibleTime);
	~DamageableEnemyComponent();
	void receiveMessage(Message* msg);
	void update();
	void receiveDamage(MCAttackType attackType, float damage);
private:
	float damage = 0;
	Timer * damageTimer;//Se usa para que la ulti no se ejecute al instante
	bool timerOn = false;
	bool attacked = false;//Si ha recibido daño
	Enemy* enemy;
	MainCharacter* mc;

	Timer * attackedTimer;//Para que tenga unos segundos de invencibilidad
	float invincibleTime;
};

