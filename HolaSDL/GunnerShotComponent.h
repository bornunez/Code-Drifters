#pragma once
#include "checkML.h"
#include "UpdateComponent.h"
#include "Vector2D.h"
#include "Timer.h"

class GunnerShotComponent :	public UpdateComponent
{
public:
	void update();
	GunnerShotComponent(Enemy* o, GameObject* target, float dist, float delay);
	virtual ~GunnerShotComponent();
	void receiveMessage(Message * msg);
	void handleAnimation();
	void updateGunPosition();
private:
	GameObject* targetObject;
	Enemy* eg;
	Timer* lastShotTime;
	Timer* shotAnimationTime;
	float distance;
	float shotDelay;
	Vector2D gunPosition;
	void shoot();


};

