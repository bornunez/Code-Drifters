#pragma once
#include "InputComponent.h"
#include "Vector2D.h"
#include "Timer.h"

class MCAttackComponent : public InputComponent
{
private:
	Vector2D aux;
	Timer* attackCD;
public:
	MCAttackComponent(GameObject* o);
	void handleEvents(SDL_Event & e);
	void recieveMessage(std::string msg) {};
	virtual ~MCAttackComponent();

};