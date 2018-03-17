#pragma once
#include "RenderComponent.h"
#include <map>
#include "Animation.h"
class GunnerAnimationComponent :
	public RenderComponent
{
public:
	GunnerAnimationComponent(GameObject* o, std::map<const char*, Animation*> anim);
	virtual ~GunnerAnimationComponent();
	void render();
	void recieveMessage(std::string msg);
	void debugBoxes();
	void debugHitbox(string box);
private:
	std::map<const char*, Animation*> animations;

};
