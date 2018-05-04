#pragma once
#include "UpdateComponent.h"
#include "Vector2D.h"
#include "Timer.h"
class EnemyBomb;

class BombComponent :	public UpdateComponent
{
public:
	void update();
	BombComponent(GameObject* o, int bulletsNumber, float time, float speed);
	~BombComponent();
	void receiveMessage(std::string msg) {};
	void handleAnimation();
private:
	EnemyBomb* eb;
	Timer* bombTimer;
	float nBullets;
	float explodeTime;
	float bombSpeed;
	void explode();

};

