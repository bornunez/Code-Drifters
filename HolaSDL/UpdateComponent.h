#pragma once
#include "Component.h"
class UpdateComponent :
	public Component
{
public:
	UpdateComponent();
	~UpdateComponent();
	virtual void update() = 0;
};

