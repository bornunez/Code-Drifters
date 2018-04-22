#pragma once
#include "UpdateComponent.h"
#include "Timer.h"

class MainCharacter;

class MCManagerComponent : public UpdateComponent
{
private:
	MainCharacter * mc;
	float gunAngle = 0;
	Timer* gunTimer;
	Timer* hurtTimer;
	float hurtTime = 0.2;

	void HurtMC(float dmg);
public:
	MCManagerComponent(MainCharacter* o);
	~MCManagerComponent();
	void receiveMessage(Message* msg);
	virtual void update();
};

