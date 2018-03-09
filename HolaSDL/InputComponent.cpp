#pragma once
#include "InputComponent.h"



InputComponent::InputComponent(GameObject* o): Component(o)
{
	type = InputC;
}


InputComponent::~InputComponent()
{
}
