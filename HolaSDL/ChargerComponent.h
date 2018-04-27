#pragma once
#include "ChaseComponent.h"
#include "ChargeComponent.h"
#include "PlayState.h"
#include "Camera.h"
class EnemyCharger;
class ChargerComponent : public ChaseComponent, public ChargeComponent
{
private:
	Timer* timer;
	EnemyCharger* ec;
	GameObject* targetObject;
	float chargeDelay, attackDelay, attackTime;
public:
	ChargerComponent(GameObject* o, GameObject* target, float cDelay, float aDelay, float aTime, float velMultiplier);
	virtual ~ChargerComponent();
	void update();
	void receiveMessage(Message* msg);
	
};

