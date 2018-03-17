#pragma once
#include "RenderComponent.h"
#include <map>
#include "Animation.h"
class MCAnimationComponent :
	public RenderComponent
{
public:
	MCAnimationComponent(GameObject* o, std::map<const char*, Animation*> anim);
	void render();
	void recieveMessage(std::string msg);
	virtual ~MCAnimationComponent();	
	void debugBoxes();
	void debugHitbox(string box);
	void handleAnimationStates();
private:
	std::map<const char*, Animation*> animations;
	
};

