#pragma once
#include "UpdateComponent.h"



UpdateComponent::UpdateComponent(GameObject* o) : Component(o)
{
	type = UpdateC;
}


UpdateComponent::~UpdateComponent()
{
}
