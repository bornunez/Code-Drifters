#pragma once
#include "checkML.h"
#include "Component.h"
class RenderComponent : public Component
{
public:
	virtual void render() {};
	virtual void lateRender() {};
	RenderComponent(GameObject* o);
	virtual ~RenderComponent();
};

