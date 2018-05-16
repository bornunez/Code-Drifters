#pragma once
#include "checkML.h"
#include "UpdateComponent.h"
#include "Vector2D.h"

class GunnerBulletComponent :
	public UpdateComponent
{
private: 
	Vector2D velocity;
public:
	void update();
	void receiveMessage(Message* msg) {};
	GunnerBulletComponent(GameObject* o);
	virtual ~GunnerBulletComponent();
};

