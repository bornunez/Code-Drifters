#pragma once
#include "RenderComponent.h"
#include "Animation.h"
#include <map>
class MCAnimationComponent :
	public RenderComponent
{
public:
	MCAnimationComponent(GameObject* o);
	void render();
	void recieveMessage(std::string msg);
	virtual ~MCAnimationComponent();
	void createAnimations();
	void Play(const char* animName);

private:
	std::map<const char*, Animation*> animations;
	Animation* currentAnimation;
	Animation* walkLeft;
	Animation* walkRight;
};

