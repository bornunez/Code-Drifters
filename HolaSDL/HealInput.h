#pragma once
#include "InputComponent.h"
class MainCharacter;
class HealInput :
	public InputComponent
{
protected:
	MainCharacter * mc;
public:
	HealInput(GameObject * o);
	virtual ~HealInput();
	void handleEvents(SDL_Event & e);
};

