#pragma once
#include "Component.h"
class InputComponent :
	public Component
{
public:
	virtual void handleEvents(SDL_Event & e) = 0;
	InputComponent();
	~InputComponent();
};

