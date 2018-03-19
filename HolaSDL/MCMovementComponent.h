#pragma once
#include "UpdateComponent.h"
#include "Vector2D.h"

class MCMovementComponent : public UpdateComponent
{
private:
	bool debug;
	float maxVelocity;
	Vector2D velocity;
	Vector2D direction;
	SDL_Keycode debugKey = SDL_SCANCODE_SPACE;

	bool keyPressed;
public:
	void update();
	void receiveMessage(std::string msg) {};
	MCMovementComponent(GameObject* o);
	virtual ~MCMovementComponent();
};

