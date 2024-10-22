#pragma once
//#include "checkML.h"
#include "UpdateComponent.h"
#include "MainCharacter.h"
#include "Timer.h"
class Enemy;

class DamageableEnemyComponent : virtual public UpdateComponent
{
public:
	DamageableEnemyComponent(Enemy* o, MainCharacter* mc, float invincibleTime);
	virtual ~DamageableEnemyComponent();
	void receiveMessage(Message* msg);
	void update();
	void receiveDamage(float damage);
private:
	float damage = 0;
	Timer * damageTimer;//Se usa para que la ulti no se ejecute al instante
	bool timerOn = false;
	bool attacked = false;//Si ha recibido da�o
	Enemy* enemy;
	MainCharacter* mc;

	Timer * attackedTimer;//Para que tenga unos segundos de invencibilidad
	float invincibleTime;
};

