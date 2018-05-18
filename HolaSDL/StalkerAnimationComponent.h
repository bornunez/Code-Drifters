#pragma once
//#include "checkML.h"
#include "RenderComponent.h"
#include <map>
#include "Animation.h"
#include "Timer.h"
class EnemyStalker;
class StalkerAnimationComponent :
	public RenderComponent
{
public:
	StalkerAnimationComponent(EnemyStalker* o, GameObject* target, std::map<const char*, Animation*> anim, float hTime, float delayTime);
	virtual ~StalkerAnimationComponent();
	void render();
	void receiveMessage(Message* msg);
	void handleAnimation();
private:
	GameObject* target;
	EnemyStalker* es;
	std::map<const char*, Animation*> animations;
	Timer* hurtTimer;
	Timer* chargeTimer;
	float hurtTime;
	float attackDelay;
};

