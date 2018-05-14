#pragma once
#include "Component.h"
class RenderComponent : public Component
{
public:
	virtual void render() {};
	virtual void lateRender() {};
	RenderComponent(GameObject* o);
	virtual ~RenderComponent();
};

