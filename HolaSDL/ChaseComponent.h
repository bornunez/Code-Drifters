#pragma once
#include "UpdateComponent.h"
#include "Vector2D.h"

class ChaseComponent : virtual public UpdateComponent
{
public:
	void update();
	void receiveMessage(Message* msg) {};
	ChaseComponent(Enemy* o, GameObject* target, float distance);
	virtual ~ChaseComponent();

private:
	GameObject* targetObject;
	Enemy* ec;
	bool rotating = false;
	float distancia;
	float angle = 0;
};

