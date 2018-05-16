#pragma once
//#include "checkML.h"
#include "ChaseComponent.h"
#include "ChargeComponent.h"
#include "PlayState.h"
#include "Camera.h"
class ChargerComponent : public ChaseComponent, public ChargeComponent
{
private:
	Timer* timer;
	Enemy* ec;
	GameObject* targetObject;
	float chargeDelay, attackDelay, attackTime;
public:
	ChargerComponent(Enemy* o, GameObject* target, float cDelay, float aDelay, float aTime, float velMultiplier);
	virtual ~ChargerComponent();
	void update();
	void receiveMessage(Message* msg);
	
};

