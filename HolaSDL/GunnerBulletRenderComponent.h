#pragma once
#include "RenderComponent.h"
class GunnerBulletRenderComponent : public RenderComponent
{
public:
	void render();
	void receiveMessage(std::string msg) {};
	GunnerBulletRenderComponent(GameObject* o);
	virtual ~GunnerBulletRenderComponent();
};

