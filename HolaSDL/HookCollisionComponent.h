#pragma once
#include "UpdateComponent.h"
class HookCollisionComponent :
	public UpdateComponent
{
public:
	HookCollisionComponent(GameObject* o);
	virtual ~HookCollisionComponent();
	void checkCollision();
	void receiveMessage(std::string msg) {};
	void update();
};

