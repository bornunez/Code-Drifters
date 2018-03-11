#pragma once
#include "UpdateComponent.h"
#include "Vector2D.h"

class GunnerBulletComponent :
	public UpdateComponent
{
private: 
	Vector2D velocity;
public:
	void update();
	void recieveMessage(std::string msg) {};
	GunnerBulletComponent(GameObject* o);
	virtual ~GunnerBulletComponent();
};

