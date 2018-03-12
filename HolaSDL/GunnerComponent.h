#pragma once
#include "UpdateComponent.h"
#include "Vector2D.h"
#include "Timer.h"

class GunnerComponent :
	public UpdateComponent
{
public:
	void update();
	void recieveMessage(std::string msg) {};
	GunnerComponent(GameObject* o, GameObject* target, float vel, float dist);
	virtual ~GunnerComponent();

private:
	Vector2D gunnerPosition;
	Vector2D targetPosition;
	GameObject* targetObject;
	Timer* lastShotTime;
	float velocity;
	float angle;
	float distancia;
	void shoot();
	bool hadisparaoxd = false;

};