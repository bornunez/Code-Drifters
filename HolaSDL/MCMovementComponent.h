#pragma once
#include "UpdateComponent.h"
#include "Vector2D.h"
class MCMovementComponent :
	public UpdateComponent
{
private:
	SDL_Keycode downKey;
	SDL_Keycode upKey;
	SDL_Keycode rightKey;
	SDL_Keycode leftKey;
	float maxVelocity;
	Vector2D velocity;
	Vector2D direction;
	float reductionFactor;
	float acceleration;
	bool keyPressed;
public:
	void update();
	void recieveMessage(std::string msg) {};
	MCMovementComponent(GameObject* o, SDL_Scancode up, SDL_Scancode right, SDL_Scancode down, SDL_Scancode left);
	virtual ~MCMovementComponent();
};

