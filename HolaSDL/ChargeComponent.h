#pragma once
#include "UpdateComponent.h"
#include "Vector2D.h"
#include "Timer.h"

class ChargeComponent :
	public UpdateComponent
{
public:
	void update();
	void recieveMessage(std::string msg) {};
	ChargeComponent(GameObject* o, float delay, float time, float velMultiplier);
	virtual ~ChargeComponent();

private:
	bool charging = false;
	Timer* timer;
	GameObject* targetObject;
	float chargeDelay;
	float velocityMult;
	float angle;
	float chargeTime;
};
