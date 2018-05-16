#pragma once
#include "checkML.h"
#include "UpdateComponent.h"
#include "MainCharacter.h"
class Enemy;

class ChargerDamageableEnemyComponent : virtual public UpdateComponent
{
public:
	ChargerDamageableEnemyComponent(Enemy* o, MainCharacter* mc, float invincibleTime);
	virtual ~ChargerDamageableEnemyComponent();
	void receiveMessage(Message* msg);
	void update();
	void receiveDamage(MCAttackType attackType, float damage);
private:
	Enemy* enemy;
	MainCharacter* mc;

	float damage = 0;
	Timer * damageTimer;//Se usa para que la ulti no se ejecute al instante
	bool timerOn = false;
	bool attacked = false;//Si ha recibido daño

	Timer * attackedTimer;//Para que tenga unos segundos de invencibilidad
	float invincibleTime;
};

