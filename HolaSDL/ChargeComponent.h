#pragma once
#include "UpdateComponent.h"
#include "Vector2D.h"
#include "Timer.h"
class Enemy;
class ChargeComponent : virtual public UpdateComponent
{
private:
	bool charging = false;
	Timer* timer;
	GameObject* targetObject;
	Enemy* e;
	float chargeDelay;
	float velocityMult;
	float angle;
	float chargeTime;
	Vector2D auxVel;

public:
	void update();
	void startCharge();
	ChargeComponent(Enemy* o, GameObject* target, float delay, float time, float velMultiplier);
	virtual ~ChargeComponent();

protected:
	void resetTimer() { this->timer->restart(); }
};
