#pragma once
//#include "checkML.h"
#include "UpdateComponent.h"
#include "Vector2D.h"
class MCBulletComponent :
	public UpdateComponent
{
private: 
	Vector2D velocity;
public:
	void update();
	void receiveMessage(std::string msg) {};
	MCBulletComponent(GameObject* o, float maxVelocity);
	virtual ~MCBulletComponent();
};

