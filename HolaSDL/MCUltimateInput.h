#pragma once
#include "InputComponent.h"
class MainCharacter;
class MCUltimateInput :
	public InputComponent
{
private:
	MainCharacter * mc;
public:
	MCUltimateInput(MainCharacter* o);
	void handleEvents(SDL_Event & e);
	void receiveMessage(Message* msg);
	virtual ~MCUltimateInput();
};

