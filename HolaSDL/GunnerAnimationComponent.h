#pragma once
#include "RenderComponent.h"
#include <map>
#include "Animation.h"
class GunnerAnimationComponent :
	public RenderComponent
{
public:
	GunnerAnimationComponent(GameObject* o, GameObject* target, std::map<const char*, Animation*> anim);
	virtual ~GunnerAnimationComponent();
	void render();
	void receiveMessage(Message * msg);
	void handleAnimations();
private:
	std::map<const char*, Animation*> animations;
	GameObject* target;
};
