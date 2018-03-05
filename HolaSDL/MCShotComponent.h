#pragma once
#include "GameObject.h"

class MCMovementComponent : public InputComponent
{
private:
	Vector2D aux;
public:
	virtual void handleEvents(SDL_Event & e);

};