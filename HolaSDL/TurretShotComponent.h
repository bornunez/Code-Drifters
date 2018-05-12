#pragma once
#include "UpdateComponent.h"
#include "Vector2D.h"
#include "Timer.h"

class TurretShotComponent :	public UpdateComponent
{
public:
	void update();
	TurretShotComponent(Enemy* o, GameObject* target, float dist, float delay);
	~TurretShotComponent();
	void receiveMessage(std::string msg) {};
	void handleAnimation();
	void updateGunPosition();
private:
	Enemy* et;
	GameObject* targetObject;
	Timer* lastShotTimer;
	float distance;
	float shotDelay;
	Vector2D gunPosition;
	void shoot();

};

