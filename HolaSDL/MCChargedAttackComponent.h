#pragma once
//#include "checkML.h"
#include "Vector2D.h"
#include "Timer.h"
#include "UpdateComponent.h"
#include "Timer.h"
class MainCharacter;
class MCChargedAttackComponent :
	public UpdateComponent
{
private:
	MainCharacter* mc;
	float chargeTime;
	Timer* chargeHold;
public:
	MCChargedAttackComponent(MainCharacter* mc, float chargeTime);
	virtual ~MCChargedAttackComponent();
	void update();
	virtual void receiveMessage(Message* msg);
};

