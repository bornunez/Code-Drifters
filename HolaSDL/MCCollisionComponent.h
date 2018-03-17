#pragma once
#include "UpdateComponent.h"
class MCCollisionComponent :
	public UpdateComponent
{
public:
	MCCollisionComponent(GameObject* o);
	virtual ~MCCollisionComponent();
	void checkCollision();
	void recieveMessage(std::string msg) {};
	void update();
};

