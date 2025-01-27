#pragma once
//#include "checkML.h"
#include "UpdateComponent.h"
#include "Vector2D.h"
#include "Timer.h"

class BombComponent :	public UpdateComponent
{
public:
	void update();
	BombComponent(Enemy* e, int bulletsNumber, float time, float speed);
	virtual ~BombComponent();
	void receiveMessage(Message* msg);
private:
	Enemy* eb;
	Timer* bombTimer;
	float nBullets;
	float explodeTime;
	float bombSpeed;
	void explode();

};

