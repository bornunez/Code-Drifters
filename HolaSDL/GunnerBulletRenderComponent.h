#pragma once
#include "RenderComponent.h"
class GunnerBulletRenderComponent :
	public RenderComponent
{
public:
	void render();
	void recieveMessage(std::string msg) {};
	GunnerBulletRenderComponent(GameObject* o);
	virtual ~GunnerBulletRenderComponent();
};

