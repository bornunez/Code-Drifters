#pragma once
#include "RenderComponent.h"
#include <map>
#include "Animation.h"
class MCAnimationComponent : public RenderComponent
{
public:
	MCAnimationComponent(GameObject* o, std::map<const char*, Animation*> anim);
	void render();
	void receiveMessage(Message* msg);
	virtual ~MCAnimationComponent();	
	void handleAnimationStates();
private:
	std::map<const char*, Animation*> animations;
	
};

