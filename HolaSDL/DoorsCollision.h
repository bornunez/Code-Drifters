#pragma once
#include "UpdateComponent.h"
class DoorsCollision :
	public UpdateComponent
{
public:
	DoorsCollision(GameObject* o);
	virtual ~DoorsCollision();
	virtual void update();
};

