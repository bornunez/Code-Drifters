#pragma once
#include "UpdateComponent.h"
#include "Timer.h"

class Enemy;

class StunComponent :
	public UpdateComponent
{
protected:
	Timer stunTimer;
	float stunTime;
	Enemy* enemy;
public:
	StunComponent(GameObject * o);
	virtual ~StunComponent();
	virtual void update();
	virtual void receiveMessage(Message* msg);
};

