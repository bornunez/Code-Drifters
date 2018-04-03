#pragma once
#include "UpdateComponent.h"
#include "Timer.h"
class BasicInvincibleComponent :
	public UpdateComponent
{
private:
	Timer * timer;
	float invincibleTime;
public:
	BasicInvincibleComponent(GameObject* o, float invincibleTime);
	virtual ~BasicInvincibleComponent();
	void update();
	void receiveMessage(std::string msg) {};
};

