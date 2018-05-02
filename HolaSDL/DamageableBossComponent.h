#pragma once
#include "UpdateComponent.h"
#include "MasterBoss.h"
class MainCharacter;
class Boss;
class DamageableBossComponent : virtual public UpdateComponent
{
public:
	DamageableBossComponent(MasterBoss* o, GameObject* mc);
	~DamageableBossComponent();
	void receiveMessage(Message* msg);
	void update() {}
	void receiveDamage(std::string attackType, float damage);
private:
	MasterBoss * boss;
	MainCharacter* mc;
};

