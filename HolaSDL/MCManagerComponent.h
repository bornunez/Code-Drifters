#pragma once
//#include "checkML.h"
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
	float hurtTime = 0.4;
	bool hurt = false;//Si ha recibido daño

	void HurtMC(float dmg);
public:
	MCManagerComponent(MainCharacter* o);
	virtual ~MCManagerComponent();
	void receiveMessage(Message* msg);
	virtual void update();
};

