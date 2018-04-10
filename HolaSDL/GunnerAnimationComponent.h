#pragma once
#include "RenderComponent.h"
#include <map>
#include "Animation.h"
#include "Timer.h"
class GunnerAnimationComponent : public RenderComponent
{
public:
	GunnerAnimationComponent(GameObject* o, GameObject* target, std::map<const char*, Animation*> anim);
	virtual ~GunnerAnimationComponent();
	void render();
	void receiveMessage(Message* msg);
	void handleAnimations();
	void hurtAnimations();
	void deathAnimations();
private:
	std::map<const char*, Animation*> animations;
	GameObject* target;
	Timer* hurtTimer;
};
