#pragma once
#include "UpdateComponent.h"
#include "Vector2D.h"

class GunnerComponent :
	public UpdateComponent
{
public:
	void update();
	void receiveMessage(Message* msg);
	GunnerComponent(GameObject* o, GameObject* target, float dist);
	virtual ~GunnerComponent();

private:
	GameObject* targetObject;
	float velocity;
	float distancia;

};