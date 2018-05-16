#pragma once
#include "checkML.h"
#include "UpdateComponent.h"
#include "Vector2D.h"
#include "Timer.h"

class BomberComponent :
	public UpdateComponent
{
public:
	void update();
	void receiveMessage(std::string msg) {};
	BomberComponent(Enemy* e, GameObject* target, float dist);
	virtual ~BomberComponent();

private:
	bool rotating = false;
	GameObject* targetObject;
	float velocity;
	float distancia;
	float angle=0;
	Enemy* eb;
	Timer* bombTimer;

};