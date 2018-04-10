#pragma once
#include "ChaseComponent.h"
#include "ChargeComponent.h"
class StalkerComponent : public ChaseComponent, public ChargeComponent
{
private:
	Timer* timer;

public:
	StalkerComponent(GameObject* o, GameObject* target, float delay, float time, float velMultiplier);
	virtual ~StalkerComponent();
	void update();
	void receiveMessage(Message* msg) {};
	
};

