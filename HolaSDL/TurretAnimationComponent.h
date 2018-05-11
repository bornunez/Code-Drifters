#pragma once
#include "RenderComponent.h"
#include <map>
#include "Animation.h"
#include "Timer.h"
class TurretAnimationComponent : public RenderComponent
{
public:
	TurretAnimationComponent(Enemy* o, GameObject* target, std::map<const char*, Animation*> anim);
	virtual ~TurretAnimationComponent();
	void render();
	void receiveMessage(Message* msg);
	void handleAnimations();
	
private:
	std::map<const char*, Animation*> animations;
	GameObject* target;
	Timer* alertTimer;
	Enemy* et;
};
