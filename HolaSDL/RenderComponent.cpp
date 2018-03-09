#pragma once
#include "RenderComponent.h"



RenderComponent::RenderComponent(GameObject* o) : Component(o)
{
	type = RenderC;
}


RenderComponent::~RenderComponent()
{
}
