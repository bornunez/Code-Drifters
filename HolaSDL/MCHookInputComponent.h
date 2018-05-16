#pragma once
#include "checkML.h"
#include "InputComponent.h"
#include "Vector2D.h"
#include "Timer.h"
class MainCharacter;
class MCHookInputComponent : public InputComponent
{
private:
	Vector2D cursorPos;
	Timer* lastReloadTime;
	MainCharacter* mc;
public:
	MCHookInputComponent(MainCharacter* mc);
	void handleEvents(SDL_Event & e);
	void receiveMessage(std::string msg) {};
	virtual ~MCHookInputComponent();

};