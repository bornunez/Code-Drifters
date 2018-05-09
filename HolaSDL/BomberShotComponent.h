#pragma once
#include "UpdateComponent.h"
#include "Vector2D.h"
#include "Timer.h"

class BomberShotComponent :	public UpdateComponent
{
public:
	void update();
	BomberShotComponent(Enemy* e, GameObject* target, float dist, float delay);
	~BomberShotComponent();
	void receiveMessage(Message* msg);
	void handleAnimation();
private:
	GameObject* targetObject;
	Enemy* eb;
	Timer* lastShotTime;
	Timer* shotAnimationTime;
	Vector2D bombPosition;
	float distance;
	float shotDelay;
	void shoot();

};

