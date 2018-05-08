#pragma once
#include "ChaseComponent.h"
#include "ChargeComponent.h"

class StalkerComponent : public ChaseComponent, public ChargeComponent
{
private:
	Timer* timer;
	Enemy* es;
	float chargeDelay, attackDelay, attackTime;
	GameObject* target;

public:
	StalkerComponent(Enemy* e, GameObject* target, float cDelay, float aDelay, float aTime, float velMultiplier);
	virtual ~StalkerComponent();
	void update();
	void receiveMessage(Message* msg);
	
};

