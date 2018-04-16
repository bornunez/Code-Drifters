#pragma once
#include "ChaseComponent.h"
#include "ChargeComponent.h"
class EnemyStalker;

class StalkerComponent : public ChaseComponent, public ChargeComponent
{
private:
	Timer* timer;
	EnemyStalker* es;
	float chargeDelay, attackDelay, attackTime;

public:
	StalkerComponent(GameObject* o, GameObject* target, float cDelay, float aDelay, float aTime, float velMultiplier);
	virtual ~StalkerComponent();
	void update();
	void receiveMessage(Message* msg) {};
	
};

