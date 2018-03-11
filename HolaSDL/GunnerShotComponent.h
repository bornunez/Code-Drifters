#pragma once
#include "UpdateComponent.h"
#include "Vector2D.h"
#include "Timer.h"

class GunnerShotComponent :	public UpdateComponent
{
public:
	void update();
	GunnerShotComponent(GameObject* o, GameObject* target, float vel, float dist);
	~GunnerShotComponent();
	void recieveMessage(std::string msg) {};

private:
	GameObject* targetObject;
	Timer* lastShotTime;
	float distance;
	float velocity;
	void shoot();
	bool hadisparaoxd = false;
};

