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
	float specificTime;
	Enemy* enemy;
public:
	StunComponent(GameObject * o, float time);
	virtual ~StunComponent();
	virtual void update();
	virtual void receiveMessage(Message* msg);
};

