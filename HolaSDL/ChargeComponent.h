#pragma once
#include "UpdateComponent.h"
#include "Vector2D.h"
#include "Timer.h"

class ChargeComponent :
	public UpdateComponent
{
public:
	void update();
	void receiveMessage(std::string msg) {};
	ChargeComponent(GameObject* o, GameObject* target, float delay, float time, float velMultiplier);
	virtual ~ChargeComponent();

private:
	bool charging = false;
	Timer* timer;
	GameObject* targetObject;
	float chargeDelay;
	float velocityMult;
	float angle;
	float chargeTime;
	Vector2D auxVel;
};
