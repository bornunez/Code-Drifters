#pragma once
#include "UpdateComponent.h"
#include "Timer.h"

class Enemy;

class WallStunComponent :
	public UpdateComponent
{
protected:
	Timer stunTimer;
	float stunTime;
	Enemy* enemy;
public:
	WallStunComponent(GameObject * o, float time);
	virtual ~WallStunComponent();
	virtual void update();
	virtual void receiveMessage(Message* msg);
};

