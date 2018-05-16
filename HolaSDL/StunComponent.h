#pragma once
#include "checkML.h"
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
	StunComponent(Enemy * o, float time);
	virtual ~StunComponent();
	virtual void update();
	virtual void receiveMessage(Message* msg);
};

