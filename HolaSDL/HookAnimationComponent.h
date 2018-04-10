#pragma once
#include "RenderComponent.h"
class Hook;
class HookAnimationComponent :
	public RenderComponent
{
public:
	HookAnimationComponent(Hook* o);
	void receiveMessage(std::string msg) {};
	void render();
	virtual ~HookAnimationComponent();
private:
	Hook * hook;
};

