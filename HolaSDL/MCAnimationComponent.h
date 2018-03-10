#pragma once
#include "RenderComponent.h"
#include "Animation.h"
class MCAnimationComponent :
	public RenderComponent
{
public:
	MCAnimationComponent(GameObject* o);
	void render();
	void recieveMessage(std::string msg);
	virtual ~MCAnimationComponent();
	void createAnimations();
	void changeAnimation(Animation* anim);
private:
	Animation* currentAnimation;
	Animation* walkLeft;
	Animation* walkRight;
};

