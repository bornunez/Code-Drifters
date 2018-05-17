#pragma once
//#include "checkML.h"
#include "ChaseComponent.h"
#include "ChargeComponent.h"
class MainCharacter;
class StalkerComponent : public ChaseComponent, public ChargeComponent
{
private:
	Timer* timer;
	Enemy* es;
	float chargeDelay, attackDelay, attackTime;
	MainCharacter* target;

public:
	StalkerComponent(Enemy* e, MainCharacter* target, float cDelay, float aDelay, float aTime, float velMultiplier);
	virtual ~StalkerComponent();
	void update();
	void receiveMessage(Message* msg);
	
};

