#pragma once
//#include "checkML.h"
#include "Component.h"
class UpdateComponent : public Component
{
public:
	UpdateComponent(GameObject * o);
	virtual ~UpdateComponent(); 
	virtual void update() = 0;
};

