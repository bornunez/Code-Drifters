#pragma once
#include "checkML.h"
#include "Component.h"
class InputComponent :
	public Component
{
public:
	virtual void handleEvents(SDL_Event & e) = 0;
	InputComponent(GameObject * o);
	virtual ~InputComponent();
};

