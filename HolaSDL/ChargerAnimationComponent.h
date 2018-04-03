#pragma once
#include "RenderComponent.h"
#include <map>
#include "Animation.h"
class ChargerAnimationComponent :
	public RenderComponent
{
public:
	ChargerAnimationComponent(GameObject* o, GameObject* target, std::map<const char*, Animation*> anim);
	virtual ~ChargerAnimationComponent();
	void render();
	void receiveMessage(std::string msg);
	void handleAnimation();
private:
	GameObject * target;
	std::map<const char*, Animation*> animations;
	
};

