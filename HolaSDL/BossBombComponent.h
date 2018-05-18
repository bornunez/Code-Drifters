#pragma once
//#include "checkML.h"
#include "UpdateComponent.h"
#include "Vector2D.h"
#include "Timer.h"

class BossBombComponent :	public UpdateComponent
{
public:
	void update();
	BossBombComponent(Enemy* e, int bulletsNumber, float time, float speed);
	virtual ~BossBombComponent();
	void receiveMessage(Message* msg);
private:
	Enemy* eb;
	Timer* bombTimer;
	float nBullets;
	float explodeTime;
	float bombSpeed;
	void explode();

};

