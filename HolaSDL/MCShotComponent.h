#pragma once
#include "InputComponent.h"
#include "Vector2D.h"

class MCMovementComponent : public InputComponent
{
private:
	Vector2D aux;
public:
	virtual void handleEvents(SDL_Event & e);

};