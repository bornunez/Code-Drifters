#pragma once
#include "Component.h"
class UpdateComponent : public Component
{
public:
	UpdateComponent();
	~UpdateComponent(); // argghhhhh
	virtual void update() = 0;
};

