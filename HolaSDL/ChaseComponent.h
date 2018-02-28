#pragma once
#include "Component.h"
#include "GameObject.h"

class ChaseComponent :public Component
{
public:
	ChaseComponent();
	~ChaseComponent();
	void update();

private:
	Vector2D position;
	Vector2D target;
	Vector2D velocity;
	double angle;
};

