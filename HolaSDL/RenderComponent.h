#pragma once
#include "Component.h"
class RenderComponent :
	public Component
{
public:
	virtual void render() = 0;
	RenderComponent(GameObject* o);
	~RenderComponent();
};

