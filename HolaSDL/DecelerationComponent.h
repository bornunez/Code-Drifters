#pragma once
#include "UpdateComponent.h"
class DecelerationComponent :
	public UpdateComponent
{
private:
	float reductionFactor;
	float time;
	float iniSpeed;
public:
	DecelerationComponent(GameObject * o, float redFactor, float time);
	virtual ~DecelerationComponent();
	void receiveMessage(Message* msg);
	void update();
};

