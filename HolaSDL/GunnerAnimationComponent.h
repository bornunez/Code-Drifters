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
	void receiveMessage(std::string msg);
private:
	std::map<const char*, Animation*> animations;

};
