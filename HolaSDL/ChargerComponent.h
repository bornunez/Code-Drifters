#pragma once
#include "ChaseComponent.h"
#include "ChargeComponent.h"
class EnemyCharger;
class ChargerComponent : public ChaseComponent, public ChargeComponent
{
private:
	Timer* timer;
	EnemyCharger* ec;
public:
	ChargerComponent(GameObject* o, GameObject* target, float delay, float time, float velMultiplier);
	virtual ~ChargerComponent();
	void update();
	void receiveMessage(Message* msg) {};
	
};

