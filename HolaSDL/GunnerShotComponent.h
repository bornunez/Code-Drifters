#pragma once
#include "UpdateComponent.h"
#include "Vector2D.h"
#include "Timer.h"

class GunnerShotComponent :	public UpdateComponent
{
public:
	void update();
	GunnerShotComponent(GameObject* o, GameObject* target, float dist, float delay);
	~GunnerShotComponent();
	void receiveMessage(std::string msg) {};
	void handleAnimation();
	void updateGunPosition();
private:
	GameObject* targetObject;
	Timer* lastShotTime;
	Timer* shotAnimationTime;
	float distance;
	float shotDelay;
	Vector2D gunPosition;
	void shoot();

};

