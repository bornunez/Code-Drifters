#pragma once
#include "UpdateComponent.h"
#include "Vector2D.h"
#include "Timer.h"

class BomberComponent :
	public UpdateComponent
{
public:
	void update();
	void receiveMessage(std::string msg) {};
	BomberComponent(GameObject* o, GameObject* target, float dist);
	virtual ~BomberComponent();

private:
	bool rotating = false;
	GameObject* targetObject;
	float velocity;
	float distancia;
	float angle=0;
	float angleVel = 0.007;
	Enemy* eg;
	Timer* bombTimer;

};