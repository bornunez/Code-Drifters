#pragma once
#include "ChaseComponent.h"
#include "ChargeComponent.h"

class ChargerComponent : public ChaseComponent, public ChargeComponent
{
private:
	bool charge = false;
	Timer* timer;
	bool stunned = false;

public:
	ChargerComponent(GameObject* o, GameObject* target, float delay, float time, float velMultiplier);
	virtual ~ChargerComponent();
	void update();
	void receiveMessage(Message* msg) {};
	
};

