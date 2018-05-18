#pragma once
//#include "checkML.h"
#include "RenderComponent.h"
#include <map>
#include "Animation.h"
class EnemyCharger;
class ChargerAnimationComponent : public RenderComponent
{
public:
	ChargerAnimationComponent(EnemyCharger* o, GameObject* target, std::map<const char*, Animation*> anim, float hTime, float delayTime);
	virtual ~ChargerAnimationComponent();
	void render();
	void receiveMessage(Message* msg);
	void handleAnimation();
private:
	GameObject* target;
	EnemyCharger* ec;
	std::map<const char*, Animation*> animations;
	Timer* hurtTimer;
	Timer* chargeTimer;
	float hurtTime;
	float attackDelay;
};

