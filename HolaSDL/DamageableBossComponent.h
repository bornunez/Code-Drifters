#pragma once
#include "UpdateComponent.h"
#include "MasterBoss.h"
#include "Timer.h"
#include "MainCharacter.h"
class MainCharacter;
class Boss;
class DamageableBossComponent : virtual public UpdateComponent
{
public:
	DamageableBossComponent(MasterBoss* o, GameObject* mc, float invincibleTime);
	~DamageableBossComponent();
	void receiveMessage(Message* msg);
	void update();
	void receiveDamage(MCAttackType attackType, float damage);
private:
	MasterBoss * boss;
	MainCharacter* mc;

	float damage = 0;
	Timer * damageTimer;//Se usa para que la ulti no se ejecute al instante
	bool timerOn = false;
	bool attacked = false;//Si ha recibido daño

	Timer * attackedTimer;//Para que tenga unos segundos de invencibilidad
	float invincibleTime;
};

