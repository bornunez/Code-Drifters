#pragma once
#include "UpdateComponent.h"
class Enemy;
class AcidDeathComponent : virtual public UpdateComponent
{
public:
	AcidDeathComponent(Enemy* e);
	virtual ~AcidDeathComponent();
	void receiveMessage(Message* msg);
	void update();
	Enemy* enemy;
};

