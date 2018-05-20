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
	Timer chargeTime;
	float chargedAttack;
public:
	MCChargedAttackComponent(MainCharacter* mc);
	virtual ~MCChargedAttackComponent();
	void update();
	virtual void receiveMessage(Message* msg);
};

