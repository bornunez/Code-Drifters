#pragma once
#include "UpdateComponent.h"
#include "Vector2D.h"

class BomberComponent :
	public UpdateComponent
{
public:
	void update();
	void receiveMessage(std::string msg) {};
	BomberComponent(GameObject* o, GameObject* target, float dist);
	virtual ~BomberComponent();

private:
	GameObject* targetObject;
	float velocity;
	float distancia;
	float angle=0;

};