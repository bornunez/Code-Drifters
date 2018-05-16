#pragma once
//#include "checkML.h"
#include "UpdateComponent.h"
#include "Vector2D.h"
#include "Timer.h"

class BomberShotComponent :	public UpdateComponent
{
public:
	void update();
	BomberShotComponent(Enemy* e, GameObject* target, float dist, float delay);
	virtual ~BomberShotComponent();
	void receiveMessage(Message* msg);
	void handleAnimation();
	void updateGunPosition();

private:
	GameObject* targetObject;
	Enemy* eb;
	Timer* lastShotTime;
	Timer* shotAnimationTime;
	float distance;
	float shotDelay;
	Vector2D gunPosition;

	void shoot();

};

