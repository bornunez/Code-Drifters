#pragma once
#include "Component.h"
class UpdateComponent : public Component
{
public:
	UpdateComponent(GameObject * o);
	~UpdateComponent(); 
	virtual void update() = 0;
};

