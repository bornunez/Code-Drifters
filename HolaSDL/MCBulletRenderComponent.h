#pragma once
#include "RenderComponent.h"
class MCBulletRenderComponent :
	public RenderComponent
{
public:
	void render();
	void receiveMessage(std::string msg) {};
	MCBulletRenderComponent(GameObject* o);
	virtual ~MCBulletRenderComponent();
};

