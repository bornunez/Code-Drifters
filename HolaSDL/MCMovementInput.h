#pragma once
#include "checkML.h"
#include "Vector2D.h"
#include "Timer.h"
#include "UpdateComponent.h"
class MainCharacter;
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
	MainCharacter* mc;
public:
	MCMovementInput(MainCharacter* o, SDL_Scancode up, SDL_Scancode right, SDL_Scancode down, SDL_Scancode left);
	virtual ~MCMovementInput();
	Vector2D aux;
	Timer* lastReloadTime;
	void update();	
	virtual void receiveMessage(Message* msg);
};

