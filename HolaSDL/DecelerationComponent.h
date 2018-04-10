#pragma once
#include "UpdateComponent.h"
class DecelerationComponent :
	public UpdateComponent
{
private:
	float reductionFactor;
public:
	DecelerationComponent(GameObject* o, float redFactor);
	virtual ~DecelerationComponent();
	void update();
};

