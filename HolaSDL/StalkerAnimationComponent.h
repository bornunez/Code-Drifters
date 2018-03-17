#pragma once
#include "RenderComponent.h"
#include <map>
#include "Animation.h"
class StalkerAnimationComponent :
	public RenderComponent
{
public:
	StalkerAnimationComponent(GameObject* o, std::map<const char*, Animation*> anim);
	virtual ~StalkerAnimationComponent();
	void render();
	void recieveMessage(std::string msg);
	void debugBoxes();
	void debugHitbox(string box);
	void Play(const char* animName);
	Animation* getCurrentAnimation() { return currentAnimation; };
private:
	std::map<const char*, Animation*> animations;
	Animation* currentAnimation;
};

