#pragma once
#include "RenderComponent.h"
class MCBulletRenderComponent :
	public RenderComponent
{
public:
	void render();
	void recieveMessage(std::string msg) {};
	MCBulletRenderComponent(GameObject* o);
	virtual ~MCBulletRenderComponent();
};

