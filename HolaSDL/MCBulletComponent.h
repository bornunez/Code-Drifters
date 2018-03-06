#pragma once
#include "UpdateComponent.h"
#include "Vector2D.h"
class MCBulletComponent :
	public UpdateComponent
{
private: 
	Vector2D direction;
	Vector2D velocity;
public:
	void update();
	void recieveMessage(std::string msg) {};
	MCBulletComponent(GameObject* o, float maxVelocity);
	virtual ~MCBulletComponent();
};

