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
	void Play(const char* animName);
	void debugBoxes();
	void debugHitbox();
	void debugHurtbox();

private:
	std::map<const char*, Animation*> animations;
	Animation* currentAnimation;
};

