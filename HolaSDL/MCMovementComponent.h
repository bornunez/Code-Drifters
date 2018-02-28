#pragma once
#include "InputComponent.h"
#include "Vector2D.h"
class MCMovementComponent :	public InputComponent
{
private:
	SDL_Keycode downKey;
	SDL_Keycode upKey;
	SDL_Keycode rightKey;
	SDL_Keycode leftKey;
public:
	void update() {};
	void render() {};
	void handleEvents(SDL_Event& e);
	void recieveMessage(std::string msg) {};
	MCMovementComponent(SDL_Keycode up, SDL_Keycode right, SDL_Keycode down, SDL_Keycode left);
	virtual ~MCMovementComponent();
};

