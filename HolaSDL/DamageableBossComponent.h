#pragma once
#include "UpdateComponent.h"
class MainCharacter;
class Boss;
class DamageableBossComponent : virtual public UpdateComponent
{
public:
	DamageableBossComponent(Boss* o, GameObject* mc);
	~DamageableBossComponent();
	void receiveMessage(Message* msg);
	void update() {}
	void receiveDamage(std::string attackType, float damage);
private:
	Boss * boss;
	MainCharacter* mc;
};

