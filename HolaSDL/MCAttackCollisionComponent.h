#pragma once
#include "UpdateComponent.h"
class MCAttackCollisionComponent :
	public UpdateComponent
{
public:
	MCAttackCollisionComponent(GameObject* o);
	virtual ~MCAttackCollisionComponent();
	void checkCollision();
	void receiveMessage(std::string msg) {};
	void update();
};

