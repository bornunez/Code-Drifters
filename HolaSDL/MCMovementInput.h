#pragma once
#include "Vector2D.h"
#include "Timer.h"
#include "UpdateComponent.h"
class MCMovementInput :
	public UpdateComponent
{
private:
	bool debug = false;
	SDL_Keycode downKey;
	SDL_Keycode upKey;
	SDL_Keycode rightKey;
	SDL_Keycode leftKey;
	SDL_Keycode debugKey = SDL_SCANCODE_SPACE;
	float maxVelocity;
	Vector2D velocity;
	Vector2D direction;
	bool keyPressed;
public:
	MCMovementInput(GameObject* o, SDL_Scancode up, SDL_Scancode right, SDL_Scancode down, SDL_Scancode left);
	virtual ~MCMovementInput();
	Vector2D aux;
	Timer* lastReloadTime;
	void update();
	void receiveMessage(std::string msg) {};	
};

