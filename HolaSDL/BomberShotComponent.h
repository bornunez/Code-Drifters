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
	void receiveMessage(std::string msg) {};
	void handleAnimation();
private:
	GameObject* targetObject;
	Enemy* eb;
	Timer* lastShotTime;
	Timer* shotAnimationTime;
	float distance;
	float shotDelay;
	void shoot();

};

