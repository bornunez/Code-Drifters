#pragma once
#include "RenderComponent.h"
#include <map>
#include "Animation.h"
class StalkerAnimationComponent :
	public RenderComponent
{
public:
	StalkerAnimationComponent(GameObject* o, GameObject* target, std::map<const char*, Animation*> anim);
	virtual ~StalkerAnimationComponent();
	void render();
	void receiveMessage(std::string msg);
	void handleAnimation();
private:
	GameObject * target;
	std::map<const char*, Animation*> animations;
	
};

