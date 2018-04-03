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
	void receiveMessage(Message * msg);
	void handleAnimation();
private:
	GameObject * target;
	std::map<const char*, Animation*> animations;
	
};

